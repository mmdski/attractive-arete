/**
 * @file eel_string.h
 * @brief String interface
 */

#ifndef __EEL_STRING_H__
#define __EEL_STRING_H__

#include <stdbool.h>

#define MAXSTRLEN 1024

struct _EelString {
  long  len;
  char *string;
};

/**
 * String object
 */
typedef struct _EelString *EelString;

/**
 * @brief Creates a new string
 *
 * @details Creates a new string from a null-terminated array of characters.
 * This function returns @c NULL if creation fails. The returned string must be
 * freed with eel_string_free() when no longer in use.
 *
 * @param string null-terminated string
 * @return new string
 */
extern EelString eel_string_new(const char *string);

/**
 * @brief Frees a string
 *
 * @param s a string
 */
extern void eel_string_free(EelString s);

/**
 * @brief Copies a string
 *
 * @param s string to copy
 * @return a copy of s
 */
extern EelString eel_string_copy(EelString s);

/**
 * @brief Returns true if two strings are equal
 *
 * @param a a string
 * @param b another string
 * @return true if two strings are equal, false otherwise
 */
extern bool eel_string_eq(EelString a, EelString b);

/**
 * @brief Gets the character array contained in a string
 *
 * @param s a string
 * @param string a pointer to a character array
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int eel_string_get(EelString s, char **string);

/**
 * @brief Gets the length of a string
 *
 * @details Gets the length of a string including the null character.
 *
 * @param s a string
 * @param len a pointer to a long that contains the length of s
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int eel_string_len(EelString s, long *len);

#define eel_strlen(str) strnlen(str, MAXSTRLEN);
#define eel_strcpy(dst, src) strlcpy(dst, src, MAXSTRLEN);

#endif
