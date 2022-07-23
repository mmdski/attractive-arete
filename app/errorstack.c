#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_error.h>

#include "errorstack/file1.c"

void
check_is_err(void) {

  bool     is_error = eel_err_stack_is_err();
  EelError err;

  if (is_error) {

    err = eel_err_stack_get_err();
    printf("There is an error\n");
    char *string = malloc(MAXERRSTRING * sizeof(char));
    eel_err_str(err, string);
    printf("The error string: [%s]\n", string);
    free(string);

  } else {

    printf("There is no error\n");
  }
}

int
main(void) {

  if (raise_error() < 0)
    eel_err_stack_push(__FILE__, __LINE__);

  eel_err_stack_print(__FILE__, __LINE__);

  eel_err_stack_clear();

  eel_err_stack_print(__FILE__, __LINE__);

  return EXIT_SUCCESS;
}
