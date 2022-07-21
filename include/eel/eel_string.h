/**
 * @file eel_string.h
 * @brief String interface
 */

#ifndef __EEL_STRING_H__
#define __EEL_STRING_H__

#include <string.h>

#define eel_strnlen(str, maxlen) strnlen(str, maxlen)
#define eel_strlcat(dst, src, dstsize) strlcat(dst, src, dstsize)

#ifdef __APPLE__

#define eel_strlcpy(dst, src, dstsize) strlcpy(dst, src, dstsize)

#else

#define eel_strlcpy(dst, src, dstsize) strncpy(dst, src, dstsize)

#endif

#endif
