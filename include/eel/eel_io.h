#ifndef __EEL_IO_H__
#define __EEL_IO_H__

#include <stdio.h>

#ifdef _MSC_VER

#define _BUFFER_COUNT 500

#define eel_sprintf(buffer, format, ...)                                       \
  sprintf_s(buffer, _BUFFER_COUNT, format, __VA_ARGS__)

#define eel_popen(command, mode) _popen(command, mode)

#else

#define eel_sprintf(buffer, format, ...) sprintf(buffer, format, __VA_ARGS__)

#define eel_popen(command, mode) popen(command, mode)

#endif
#endif
