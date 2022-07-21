#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include <eel/eel_error.h>
#include <eel/eel_string.h>

EelErrorType
eel_basename(const char *path, char *bname) {

  // for MSVC, check _splitpath

#ifdef __APPLE__
  // use basename_r since it is thread safe
  errno           = 0;
  char *bname_ptr = basename_r(path, bname);
  if (bname_ptr == NULL) {
    perror(path);
    return EEL_POSIX_ERROR;
  }
#endif

  return EEL_NO_ERROR;
}
