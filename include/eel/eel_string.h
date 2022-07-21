/**
 * @file eel_string.h
 * @brief String interface
 */

#ifndef __EEL_STRING_H__
#define __EEL_STRING_H__

#include <string.h>

#ifdef _MSC_VER
#include <stdlib.h>
#endif

#define eel_strnlen(str, maxlen) strnlen(str, maxlen)
#define eel_strlcat(dst, src, dstsize) strlcat(dst, src, dstsize)

#ifdef __APPLE__

#define eel_strlcpy(dst, src, dstsize) strlcpy(dst, src, dstsize)

#elif defined __GNUC__

#define eel_strlcpy(dst, src, dstsize) strncpy(dst, src, dstsize)

#elif defined _MSC_VER

#define eel_strlcpy(dst, src, dstsize) strncpy_s(dst, dstsize, src, _TRUNCATE)

#endif

#endif
