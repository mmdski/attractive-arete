#include <eel/eel_error.h>
#include <eel/eel_exit.h>

#include "test.h"

void
test_new(void) {
  EelError err = eel_err_new(EEL_INVALID_ARG_ERROR, "Argument is invalid");
  ASSERT_NONNULL(err);
  eel_err_free(err);
  EXIT_TEST
}

void
test_free(void) {
  EelError err = eel_err_new(EEL_INVALID_ARG_ERROR, "Argument is invalid");
  ASSERT_NONNULL(err);
  eel_err_free(err);
  eel_err_free(NULL);
  EXIT_TEST
}

void
test_raise(void) {
  ASSERT_FALSE(eel_err_stack_is_err());

  EelErrorType type = EEL_INVALID_ARG_ERROR;
  ASSERT_ZERO(eel_err_raise(type, "message", __FILE__, __LINE__));
  ASSERT_TRUE(eel_err_stack_is_err());

  EelError err = eel_err_stack_get_err();
  ASSERT_NONNULL(err);
  ASSERT_TRUE(eel_err_is_type(err, type));

  eel_err_stack_clear();
  ASSERT_FALSE(eel_err_stack_is_err());

  // the error should be null after the stack is cleared
  ASSERT_NULL(eel_err_stack_get_err());
  ASSERT_EQUALS(eel_err_stack_push(__FILE__, __LINE__), EEL_ERR_STACK_ERROR);

  EXIT_TEST
}

void
test_stack_check(void) {
  eel_err_stack_check(__FILE__, __LINE__);

  EXIT_TEST
}

void
test_raise_fail(void) {

  ASSERT_FALSE(eel_err_stack_is_err());

  EelErrorType type = EEL_INVALID_ARG_ERROR;
  ASSERT_ZERO(eel_err_raise(type, "message", __FILE__, __LINE__));
  ASSERT_TRUE(eel_err_stack_is_err());

  EXPECT_EXIT_CALL(eel_err_raise(type, "message", __FILE__, __LINE__))

  eel_err_stack_clear();

  EXIT_TEST
}

void
test_stack_check_fail(void) {
  eel_err_raise(EEL_INVALID_ARG_ERROR, NULL, __FILE__, __LINE__);
  eel_exit_expected_set();
  eel_err_stack_check(__FILE__, __LINE__);
  ASSERT_TRUE(eel_exit_called());
  eel_exit_called_clear();
  eel_err_stack_clear();

  EXIT_TEST
}

int
main(void) {
  RUN_TEST_FUNC(test_new)
  RUN_TEST_FUNC(test_free)
  RUN_TEST_FUNC(test_raise)
  RUN_TEST_FUNC(test_raise_fail)
  RUN_TEST_FUNC(test_stack_check)
  RUN_TEST_FUNC(test_stack_check_fail)

  return EXIT_SUCCESS;
}
