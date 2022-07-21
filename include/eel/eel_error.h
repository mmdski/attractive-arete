/**
 * @file eel_error.h
 * @brief Error definitions
 */

#ifndef __EEL_ERR_H__
#define __EEL_ERR_H__

#include <stdbool.h>

#define MAXERRNAME 25
#define MAXERRMESSAGE 120
#define MAXERRSTRING 200

/**
 * Error types
 */
typedef enum {

  /** No error */
  EEL_NO_ERROR = 0,

  /** Error in system library wrapper **/
  EEL_SYS_ERROR,

  /** Error in POSIX library wrapper **/
  EEL_POSIX_ERROR,

  /** Null argument error */
  EEL_NULL_ARG_ERROR,

  /** Invalid argument error */
  EEL_INVALID_ARG_ERROR,

  /** Memory error */
  EEL_MEM_ERROR,

  /** Value error */
  EEL_VALUE_ERROR,

  /** Error stack error **/
  EEL_ERR_STACK_ERROR,

  /** eel_exit() has been called */
  EEL_EXIT_CALLED,

  /** General error */
  GENERAL_ERROR,

  /** Number of error types **/
  NUM_ERROR_TYPES

} EelErrorType;

/**
 * eel error object
 */
typedef struct _EelError *EelError;

/**
 * @brief Creates a new error object
 *
 * @details The error object must be freed with eel_err_free().
 *
 * @param type error type
 * @param message error message
 */
extern EelError eel_err_new(EelErrorType type, const char *message);

/**
 * @brief Frees an error object.
 *
 * @param err error object
 */
extern void eel_err_free(EelError err);

/**
 * @brief Returns true if an error object is of a specified type.
 *
 * @param err an error object
 * @param type an error type
 * @returns true if @c err is of type @c type, false otherwise
 */
extern bool eel_err_is_type(EelError err, EelErrorType type);

/**
 * @brief Writes the message of an error to a character string
 *
 * @param err an error object
 * @param err_message pre-allocated character string
 * @return EelErrorType error indicator
 */
extern EelErrorType eel_err_message(EelError err, char *err_message);

/**
 * @brief Writes the name of an error to a character string
 *
 * @param err an error object
 * @param err_name pre-allocated character string
 * @return EelErrorType error indicator
 */
extern EelErrorType eel_err_name(EelError err, char *err_name);

/**
 * @brief Writes an error string to a character string
 *
 * @details An error string contains the name of an error and an error message.
 * The message will be omitted if no message was provided upon the creation of
 * @c err.
 *
 * @param err an error object
 * @param err_str pre-allocated character string
 * @return EelErrorType error indicator
 */
extern EelErrorType eel_err_str(EelError err, char *err_str);

/**
 * @brief Returns the type of an error
 *
 * @param err an error object
 * @returns the error type of @c err
 */
extern EelErrorType eel_err_type(EelError err);

/**
 * @brief Puts an error on the error stack and initializes the first line of the
 * stack
 *
 * @param type error type
 * @param message error message
 * @param file file name
 * @param line line number (use __LINE__ macro)
 * @return error indicator
 */
extern EelErrorType eel_err_raise(EelErrorType type,
                                  const char  *message,
                                  const char  *file,
                                  int          line);

/**
 * @brief Returns true if an error is on the error stack, false otherwise
 *
 * @return true or false
 */
extern bool eel_err_stack_is_err(void);

/**
 * @brief Clears the error stack
 */
extern void eel_err_stack_clear(void);

/**
 * @brief Pushes a new line on the error stack
 *
 * @param file file name
 * @param line line number (use __LINE__ macro)
 * @return error indicator
 */
extern EelErrorType eel_err_stack_push(const char *file, int line);

/**
 * @brief Returns the error currently on the error stack
 *
 * @details The returned error is a reference to the error on the stack. Do not
 * free outside of eel_err_stack_clear().
 *
 * @return error currently on the stack
 */
extern EelError eel_err_stack_get_err(void);

/**
 * @brief Checks the error type on the error stack
 *
 * @param type error type
 * @return true if @p type is the type of error on the stack
 * @return false if @p type is not the type of error on the stack
 */
extern bool eel_err_stack_is_type(EelErrorType type);

/**
 * @brief Print the error stack to @c stderr
 *
 * @param file file name (use __FILE__ macro)
 * @param line line number (use __LINE__ macro)
 */
extern void eel_err_stack_print(const char *file, int line);

/**
 * @brief Checks for an error on stack.
 *
 * @details If an error on the stack exists, prints the stack and exits the
 * program.
 *
 * @param file file name (use __FILE__ macro)
 * @param line line number (use __LINE__ macro)
 */
extern void eel_err_stack_check(const char *file, int line);

#endif
