/**
 * @file eel_string.h
 * @brief String interface
 */

#ifndef __EEL_STRING_H__
#define __EEL_STRING_H__

#define eel_strnlen(str, maxlen) strnlen(str, maxlen)
#define eel_strlcpy(dst, src, dstsize) strlcpy(dst, src, dstsize)
#define eel_strlcat(dst, src, dstsize) strlcat(dst, src, dstsize)

#endif
