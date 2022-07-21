#ifdef __GNUC__
#define _GNU_SOURCE
#include <string.h>
#elif defined __APPLE__
#include <libgen.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

#include <eel/eel_error.h>
#include <eel/eel_string.h>

EelErrorType
eel_basename(const char *path, char *bname) {

  // for MSVC, check _splitpath

#if defined __APPLE__

  // use basename_r since it is thread safe
  errno           = 0;
  char *bname_ptr = basename_r(path, bname);
  if (bname_ptr == NULL) {
    perror(path);
    return EEL_POSIX_ERROR;
  }

#elif defined __GNUC__

  char *bname_ptr = basename(path);
  eel_strlcpy(bname, bname_ptr, MAXPATHLEN);

#endif

  return EEL_NO_ERROR;
}
