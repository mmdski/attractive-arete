#ifdef __GNUC__
#define _GNU_SOURCE
#include <string.h>
#elif defined __APPLE__
#include <libgen.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _MSC_VER
#include <sys/param.h>
#else
#define MAXPATHLEN _MAX_PATH
#endif

#include <eel/eel_error.h>
#include <eel/eel_io.h>
#include <eel/eel_string.h>

#include "memory.h"

EelErrorType
eel_basename(const char *path, char *bname) {

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

#elif defined _MSC_VER

  // for MSVC, check _splitpath_s
  char *fname = eel_alloc(_MAX_FNAME * sizeof(char));
  char *ext   = eel_alloc(_MAX_EXT * sizeof(char));

  errno = 0;
  errno_t err =
      _splitpath_s(path, NULL, 0, NULL, 0, fname, _MAX_FNAME, ext, _MAX_EXT);
  if (err != 0) {
    eel_free(fname);
    eel_free(ext);
    perror(path);
    return EEL_POSIX_ERROR;
  }

  eel_snprintf(bname, _MAX_PATH, "%s.%s", fname, ext);
  eel_free(fname);
  eel_free(ext);

#endif

  return EEL_NO_ERROR;
}
