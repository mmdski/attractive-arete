#ifndef __EEL_IO_H__
#define __EEL_IO_H__

#include <stdio.h>

#ifdef _MSC_VER

#define eel_snprintf(buffer, size, format, ...)                                \
  sprintf_s(buffer, size, format, __VA_ARGS__)

#define eel_popen(command, mode) _popen(command, mode)

#else

#define eel_snprintf(buffer, size, format, ...)                                \
  snprintf(buffer, size, format, __VA_ARGS__)

#define eel_popen(command, mode) popen(command, mode)

#endif
#endif
