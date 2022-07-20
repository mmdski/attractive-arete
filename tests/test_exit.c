#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_exit.h>

#include "test.h"

int
main(void) {

  eel_exit_expected_set();
  eel_exit(EXIT_FAILURE);

  if (!eel_exit_called())
    return EXIT_FAILURE;

  if (eel_exit_status() != EXIT_FAILURE)
    return EXIT_FAILURE;

  eel_exit_expected_clear();
  eel_exit_called_clear();

  EXIT_TEST
}
