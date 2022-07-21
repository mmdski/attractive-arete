#include <string.h>

#include <eel/eel_string.h>

#include "test.h"

void
test_new(void) {
  EelString s = eel_string_new("Hello, world!");
  eel_string_free(s);

  ASSERT_NULL(eel_string_new(NULL));
}

void
test_free(void) {
  EelString s = eel_string_new("Hello, world!");
  eel_string_free(s);

  eel_string_free(NULL);
}

void
test_copy(void) {
  EelString s      = eel_string_new("Hello, world!");
  EelString s_copy = eel_string_copy(s);

  char *a;
  ASSERT_ZERO(eel_string_get(s, &a));

  char *b;
  ASSERT_ZERO(eel_string_get(s_copy, &b));

  ASSERT_ZERO(strcmp(a, b));

  eel_string_free(s);
  eel_string_free(s_copy);
}

void
test_get(void) {
  char     *string = "Hello, world!";
  EelString s      = eel_string_new(string);

  char *get_string;
  ASSERT_ZERO(eel_string_get(s, &get_string));
  ASSERT_ZERO(strcmp(get_string, string));

  eel_string_free(s);
}

void
test_eq(void) {
  EelString a      = eel_string_new("abcd");
  EelString b      = eel_string_new("efgh");
  EelString c      = NULL;
  EelString a_copy = eel_string_copy(a);

  ASSERT_TRUE(eel_string_eq(a, a));
  ASSERT_FALSE(eel_string_eq(a, c));
  ASSERT_FALSE(eel_string_eq(a, b));
  ASSERT_FALSE((a == a_copy));
  ASSERT_TRUE(eel_string_eq(a, a_copy));
  ASSERT_FALSE(eel_string_eq(NULL, NULL));

  eel_string_free(a);
  eel_string_free(b);
  eel_string_free(a_copy);
}

int
main(void) {
  RUN_TEST_FUNC(test_new)
  RUN_TEST_FUNC(test_free)
  RUN_TEST_FUNC(test_eq)
  RUN_TEST_FUNC(test_copy)
  RUN_TEST_FUNC(test_get)

  return EXIT_SUCCESS;
}
