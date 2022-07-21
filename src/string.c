#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <eel/eel_error.h>
#include <eel/eel_string.h>

#include "error.h"
#include "memory.h"

static EelString
eel_string_new_empty(long len) {
  EelString s;
  NEW(s);

  char *string = eel_calloc(len, sizeof(char));

  if (string == NULL) {
    return NULL;
  }

  s->len    = len;
  s->string = string;

  return s;
}

static int
eel_string_fill(EelString s, const char *string) {
  if (s == NULL || string == NULL)
    RAISE_NULL_ERR_INT

  long len = s->len;

  for (long i = 0; i < len; i++) {
    s->string[i] = string[i];
  }

  return 0;
}

EelString
eel_string_new(const char *string) {
  if (string == NULL)
    RAISE_NULL_ERR_NULL

  long       len     = 1;
  const long MAX_LEN = 500;

  while (true) {
    if (string[len - 1] == '\0') {
      break;
    } else if (len >= MAX_LEN) {
      break;
    } else
      len++;
  }

  EelString s = eel_string_new_empty(len);
  if (s == NULL)
    RAISE_NULL_ERR_NULL

  if (eel_string_fill(s, string) < 0) {
    eel_string_free(s);
    RAISE_NULL_ERR_NULL
  }

  return s;
}

void
eel_string_free(EelString s) {
  if (s == NULL) {
    return;
  }
  eel_free(s->string);
  FREE(s);
  return;
}

EelString
eel_string_copy(EelString s) {
  if (s == NULL)
    RAISE_NULL_ERR_NULL

  EelString s_copy = eel_string_new(s->string);

  return s_copy;
}

bool
eel_string_eq(EelString a, EelString b) {
  if (a == NULL || b == NULL)
    return false;

  if (a == b)
    return true;

  return strcmp(a->string, b->string) == 0;
}

int
eel_string_get(EelString s, char **string) {

  if (s == NULL || string == NULL)
    RAISE_NULL_ERR_INT

  *string = s->string;
  return 0;
}

int
eel_string_len(EelString s, long *len) {
  if (s == NULL || len == NULL)
    RAISE_NULL_ERR_INT

  *len = s->len;

  return 0;
}
