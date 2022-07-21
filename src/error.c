#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#include <eel/eel_error.h>
#include <eel/eel_exit.h>
#include <eel/eel_io.h>
#include <eel/eel_posix.h>
#include <eel/eel_string.h>

#include "memory.h"

struct _EelError {
  EelErrorType type;
  char        *error_name;
  char        *message;
};

EelErrorType
eel_err_type_name(EelErrorType type, char *error_name) {
  switch (type) {
  case EEL_NULL_ARG_ERROR:
    eel_strlcpy(error_name, "NullArgumentError", MAXERRNAME);
    break;
  case EEL_INVALID_ARG_ERROR:
    eel_strlcpy(error_name, "InvalidArgumentError", MAXERRNAME);
    break;
  case EEL_MEM_ERROR:
    eel_strlcpy(error_name, "MemoryError", MAXERRNAME);
    break;
  case EEL_VALUE_ERROR:
    eel_strlcpy(error_name, "ValueError", MAXERRNAME);
    break;
  case EEL_EXIT_CALLED:
    eel_strlcpy(error_name, "ExitError", MAXERRNAME);
    break;
  case GENERAL_ERROR:
    eel_strlcpy(error_name, "GeneralError", MAXERRNAME);
    break;
  default:
    eel_strlcpy(error_name, "UnnamedError", MAXERRNAME);
  }

  return EEL_NO_ERROR;
}

EelError
eel_err_new(EelErrorType type, const char *message) {
  EelError err;
  NEW(err);

  char *error_name = eel_alloc(MAXERRNAME * sizeof(char));
  if (eel_err_type_name(type, error_name)) {
    eel_free(error_name);
    FREE(err);
    return NULL;
  }

  char *error_msg;
  if (message == NULL)
    error_msg = NULL;
  else {
    error_msg = eel_alloc(MAXERRMESSAGE * sizeof(char));
    eel_strlcpy(error_msg, message, MAXERRMESSAGE);
  }

  err->type       = type;
  err->error_name = error_name;
  err->message    = error_msg;

  return err;
}

void
eel_err_free(EelError err) {

  if (err == NULL)
    return;

  eel_free(err->error_name);
  eel_free(err->message);

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

EelErrorType
eel_err_message(EelError err, char *err_message) {

  if (!err_message)
    return EEL_NULL_ARG_ERROR;

  if (err == NULL) {
    return EEL_NULL_ARG_ERROR;
  }
  if (err->message == NULL)
    return EEL_NULL_ARG_ERROR;

  eel_strlcpy(err_message, err->message, MAXERRMESSAGE);

  return EEL_NO_ERROR;
}

EelErrorType
eel_err_name(EelError err, char *error_name) {

  if (!error_name)
    return EEL_NULL_ARG_ERROR;

  if (err == NULL)
    return EEL_NULL_ARG_ERROR;

  eel_strlcpy(error_name, err->error_name, MAXERRNAME);

  return EEL_NO_ERROR;
}

EelErrorType
eel_err_str(EelError err, char *err_str) {

  if (err == NULL)
    return EEL_NULL_ARG_ERROR;

  // return the full string if message is not null
  if (err->message != NULL) {
    eel_snprintf(
        err_str, MAXERRSTRING, "%s: %s", err->error_name, err->message);
  }
  // otherwise, return only the error name
  else {
    eel_strlcpy(err_str, err->error_name, MAXERRNAME);
  }

  return EEL_NO_ERROR;
}

typedef struct _EelErrorStackNode EelErrorStackNode;

struct _EelErrorStackNode {
  int                line;
  char              *file;
  char              *string;
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

  char *bname = eel_alloc(MAXPATHLEN * sizeof(char));
  if (eel_basename(file, bname)) {
    eel_free(bname);
    FREE(node);
    return NULL;
  }

  int   node_string_len = MAXPATHLEN + 25;
  char *node_string     = eel_alloc(node_string_len * sizeof(char));
  eel_snprintf(
      node_string, node_string_len, "File \"%s\", line %i", bname, line);

  node->line   = line;
  node->file   = bname;
  node->string = node_string;
  node->next   = NULL;

  return node;
}

static EelErrorType
eel_err_stack_node_free(EelErrorStackNode *node) {
  if (node == NULL)
    return EEL_NULL_ARG_ERROR;

  eel_free(node->file);
  eel_free(node->string);
  FREE(node);

  return EEL_NO_ERROR;
}

EelErrorType
eel_err_raise(EelErrorType type,
              const char  *message,
              const char  *file,
              int          line) {
  if (stack.error != NULL) {
    fprintf(stderr, "Fatal error: Error raised while error in stack\n");
    eel_exit(EXIT_FAILURE);
#ifdef TESTING
    return EEL_EXIT_CALLED;
#endif
  }

  stack.error = eel_err_new(type, message);
  stack.node  = eel_err_stack_node_new(file, line);

  return EEL_NO_ERROR;
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

EelErrorType
eel_err_stack_push(const char *file, int line) {
  if (stack.error == NULL || stack.node == NULL)
    return EEL_ERR_STACK_ERROR;

  EelErrorStackNode *new_node = eel_err_stack_node_new(file, line);

  new_node->next = stack.node;
  stack.node     = new_node;

  return EEL_NO_ERROR;
}

bool
eel_err_stack_is_type(EelErrorType type) {
  return eel_err_is_type(stack.error, type);
}

void
eel_err_stack_print(const char *file, int line) {

  if (stack.error == NULL)
    return;

  char bname[MAXPATHLEN];
  if (eel_basename(file, bname)) {
    fprintf(stderr, "Failed to print error stack\n.");
    eel_exit(EXIT_FAILURE);
  }

  fprintf(
      stderr, "Error stack print called from \"%s\" on line %i\n", bname, line);
  fprintf(stderr, "Stack trace (most recent call last):\n");

  EelErrorStackNode *node = stack.node;
  while (node != NULL) {
    fprintf(stderr, "\t%s\n", node->string);
    node = node->next;
  }

  char *err_str = eel_alloc(MAXERRSTRING * sizeof(char));
  eel_err_str(stack.error, err_str);
  fprintf(stderr, "%s\n", err_str);
  eel_free(err_str);
}

void
eel_err_stack_check(const char *file, int line) {
  if (eel_err_stack_is_err()) {

    char bname[MAXPATHLEN];
    if (eel_basename(file, bname)) {
      fprintf(stderr, "Error stack check failed.\n");
      eel_exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Unchecked error\n");
    fprintf(stderr, "Error stack checked on \"%s\", line %i\n", bname, line);

    eel_err_stack_print(__FILE__, __LINE__);
    eel_exit(EXIT_FAILURE);
  }
}
