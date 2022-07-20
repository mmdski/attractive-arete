#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_exit.h>

#define EXIT_TEST                                                              \
  if (eel_exit_called()) {                                                     \
    fprintf(stderr,                                                            \
            "Error: eel_exit called and not cleared. File, %s line %d\n",      \
            __FILE__,                                                          \
            __LINE__);                                                         \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  printf("Test %s ran successfully\n", __FILE__);                              \
  return EXIT_SUCCESS;

#define STR(x) #x
#define RUN_TEST_FUNC(func)                                                    \
  printf("Running test function: %s\n", STR(func));                            \
  func();

#define EXPECT_EXIT_CALL(func)                                                 \
  eel_exit_expected_set();                                                     \
  func();                                                                      \
  if (!eel_exit_called()) {                                                    \
    fprintf(stderr, "Error: Expected a call to eel_exit()\n");                 \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  eel_exit_expected_clear();                                                   \
  eel_exit_called_clear();
