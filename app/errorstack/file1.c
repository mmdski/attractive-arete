#include <eel/eel_error.h>

int
raise_error(void) {
  eel_err_raise(EEL_INVALID_ARG_ERROR, "Invalid argument", __FILE__, __LINE__);
  return -1;
}
