#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_error.h>
#include <eel/eel_string.h>

int
main(void) {

  EelError err = eel_err_new(EEL_INVALID_ARG_ERROR, "Invalid argument");

  char *string = malloc(MAXERRSTRING * sizeof(char));

  if (eel_err_name(err, string))
    return EXIT_FAILURE;
  printf("Name: %s\n", string);

  if (eel_err_message(err, string))
    return EXIT_FAILURE;
  printf("Message: %s\n", string);

  EelErrorType type = eel_err_type(err);
  printf("EEL_INVALID_ARG_ERROR = %i\n", EEL_INVALID_ARG_ERROR);
  printf("Error type: %i\n", type);

  free(string);
  eel_err_free(err);

  return EXIT_SUCCESS;
}
