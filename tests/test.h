#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_error.h>
#include <eel/eel_exit.h>

#define EXIT_TEST                                                              \
  eel_err_stack_check(__FILE__, __LINE__);                                     \
  if (eel_exit_called()) {                                                     \
    fprintf(stderr,                                                            \
            "Error: eel_exit called and not cleared. File, %s line %d\n",      \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define STR(x) #x
#define RUN_TEST_FUNC(func)                                                    \
  printf("Running test function: %s\n", STR(func));                            \
  func();

#define EXPECT_EXIT_CALL(func_call)                                            \
  eel_exit_expected_set();                                                     \
  func_call;                                                                   \
  if (!eel_exit_called()) {                                                    \
    fprintf(stderr, "Error: Expected a call to eel_exit()\n");                 \
    exit(EXIT_FAILURE);                                                        \
  }                                                                            \
  eel_exit_expected_clear();                                                   \
  eel_exit_called_clear();

#define ASSERT_NULL(value)                                                     \
  if (value) {                                                                 \
    fprintf(stderr,                                                            \
            "Error: Expected NULL. File %s, line %d.\n",                       \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define ASSERT_NONNULL(value)                                                  \
  if (!value) {                                                                \
    fprintf(stderr,                                                            \
            "Error: Expected NULL. File %s, line %d.\n",                       \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define ASSERT_ZERO(value)                                                     \
  if (value) {                                                                 \
    fprintf(                                                                   \
        stderr, "Error: Expected 0. File %s, line %d.\n", __FILE__, __LINE__); \
    exit(EXIT_FAILURE);                                                        \
  }

#define ASSERT_TRUE(value)                                                     \
  if (!value) {                                                                \
    fprintf(stderr,                                                            \
            "Error: Expected true. File %s, line %d.\n",                       \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define ASSERT_FALSE(value)                                                    \
  if (value) {                                                                 \
    fprintf(stderr,                                                            \
            "Error: Expected false. File %s, line %d.\n",                      \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define ASSERT_NEGATIVE(value)                                                 \
  if (value >= 0) {                                                            \
    fprintf(stderr,                                                            \
            "Error: Expected false. File %s, line %d.\n",                      \
            __FILE__,                                                          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }
