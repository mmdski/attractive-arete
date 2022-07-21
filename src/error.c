#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_error.h>
#include <eel/eel_exit.h>
#include <eel/eel_io.h>

#include "memory.h"

struct _EelError {
  EelErrorType type;
  EelString    error_name;
  EelString    message;
};

EelString
eel_err_type_name(EelErrorType type) {
  char *error_name;
  switch (type) {
  case NULL_ARGUMENT_ERROR:
    error_name = "NullArgumentError";
    break;
  case INVALID_ARGUMENT_ERROR:
    error_name = "InvalidArgumentError";
    break;
  case MEMORY_ERROR:
    error_name = "MemoryError";
    break;
  case VALUE_ERROR:
    error_name = "ValueError";
    break;
  case EXIT_CALLED:
    error_name = "ExitError";
    break;
  case GENERAL_ERROR:
    error_name = "GeneralError";
    break;
  default:
    error_name = "UnnamedError";
  }

  return eel_string_new(error_name);
}

EelError
eel_err_new(EelErrorType type, const char *message) {
  EelError err;
  NEW(err);
  err->type       = type;
  err->error_name = eel_err_type_name(type);

  if (message == NULL)
    err->message = eel_string_new("");
  else
    err->message = eel_string_new(message);

  return err;
}

void
eel_err_free(EelError err) {
  if (err == NULL)
    return;

  eel_string_free(err->error_name);
  eel_string_free(err->message);

  FREE(err);
}

bool
eel_err_is_type(EelError err, EelErrorType type) {
  if (err == NULL)
    return false;
  return ((err->type) == type);
}

EelErrorType
eel_err_type(EelError err) {
  if (err == NULL)
    return -1;
  return err->type;
}

EelString
eel_err_message(EelError err) {
  if (err == NULL) {
    return NULL;
  }
  if (err->message == NULL)
    return NULL;

  return eel_string_copy(err->message);
}

EelString
eel_err_name(EelError err) {
  if (err == NULL) {
    return NULL;
  }

  return eel_string_copy(err->error_name);
}

EelString
eel_err_str(EelError err) {
  if (err == NULL)
    return NULL;

  char *err_name;
  if (eel_string_get(err->error_name, &err_name) < 0)
    return NULL;

  EelString err_str;

  // no message, return only the error name
  if (err->message == NULL) {
    err_str = eel_string_new(err_name);
    if (err_str == NULL)
      goto fail;
  }
  // otherwise, return the full string
  else {
    long name_len;
    if (eel_string_len(err->error_name, &name_len) < 0)
      goto fail;

    long message_len;
    if (eel_string_len(err->message, &message_len) < 0)
      goto fail;

    char *message;
    if (eel_string_get(err->message, &message) < 0)
      goto fail;

    char err_str_buffer[500];
    if (eel_sprintf(err_str_buffer, "%s: %s", err_name, message) < 0)
      goto fail;

    err_str = eel_string_new(err_str_buffer);
    if (err_str == NULL)
      goto fail;
  }

  return err_str;

fail:
  return NULL;
}

typedef struct _EelErrorStackNode EelErrorStackNode;

struct _EelErrorStackNode {
  int                line;
  EelString          file;
  EelString          string;
  EelErrorStackNode *next;
};

struct _EelErrorStack {
  EelError           error;
  EelErrorStackNode *node;
};

static struct _EelErrorStack stack = {NULL, NULL};

static EelErrorStackNode *
eel_err_stack_node_new(const char *file, int line) {
  if (file == NULL)
    return NULL;

  EelErrorStackNode *node;
  NEW(node);

  char node_string_buffer[500];

  node->line = line;
  node->file = eel_string_new(file);

  eel_sprintf(node_string_buffer, "File \"%s\", line %i", file, line);
  node->string = eel_string_new(node_string_buffer);

  node->next = NULL;

  return node;
}

static int
eel_err_stack_node_free(EelErrorStackNode *node) {
  if (node == NULL)
    return -1;

  eel_string_free(node->file);
  eel_string_free(node->string);
  FREE(node);
  return 0;
}

int
eel_err_raise(EelErrorType type,
              const char  *message,
              const char  *file,
              int          line) {
  if (stack.error != NULL) {
    fprintf(stderr, "Fatal error: Error raised while error in stack\n");
    eel_exit(EXIT_FAILURE);
#ifdef TESTING
    return EXIT_CALLED;
#endif
  }

  stack.error = eel_err_new(type, message);
  stack.node  = eel_err_stack_node_new(file, line);

  return 0;
}

bool
eel_err_stack_is_err(void) {
  return stack.error != NULL;
}

void
eel_err_stack_clear(void) {

  if (stack.error == NULL)
    return;

  eel_err_free(stack.error);
  stack.error = NULL;

  EelErrorStackNode *node      = stack.node;
  EelErrorStackNode *next_node = node->next;
  eel_err_stack_node_free(node);
  while (next_node != NULL) {
    node      = next_node;
    next_node = node->next;
    eel_err_stack_node_free(node);
  }
  stack.node = NULL;
}

EelError
eel_err_stack_get_err(void) {
  return stack.error;
}

int
eel_err_stack_push(const char *file, int line) {
  if (stack.error == NULL || stack.node == NULL)
    return -1;

  EelErrorStackNode *new_node = eel_err_stack_node_new(file, line);

  new_node->next = stack.node;
  stack.node     = new_node;

  return 0;
}

bool
eel_err_stack_is_type(EelErrorType type) {
  return eel_err_is_type(stack.error, type);
}

void
eel_err_stack_print(const char *file, int line) {
  if (stack.error == NULL)
    return;

  fprintf(stderr, "Error stack print called from %s on line %i\n", file, line);
  fprintf(stderr, "Stack trace (most recent call last):\n");

  char *string;

  EelErrorStackNode *node = stack.node;
  while (node != NULL) {
    eel_string_get(node->string, &string);
    fprintf(stderr, "\t%s\n", string);
    node = node->next;
  }

  EelString err_string = eel_err_str(stack.error);
  eel_string_get(err_string, &string);
  fprintf(stderr, "%s\n", string);
  eel_string_free(err_string);
}

void
eel_err_stack_check(const char *file, int line) {
  if (eel_err_stack_is_err()) {
    fprintf(stderr, "Unchecked error\n");
    fprintf(stderr, "Error stack checked on %s, line %i\n", file, line);
    eel_err_stack_print(__FILE__, __LINE__);
    eel_exit(EXIT_FAILURE);
  }
}
