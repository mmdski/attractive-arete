#ifndef __EEL_EXIT__
#define __EEL_EXIT__

#include <stdbool.h>

/**
 * @brief Perform normal program termination
 *
 * @details If the exit expected flag is set after using
 * eel_exit_expected_set(), the program doesn't terminate. The call status of
 * this function can be checked with eel_exit_called(), and the call flag can ge
 * cleared with eel_exit_called_clear(). The program will terminate if the
 * expected flag is not set or if the called flag has not been cleared.
 *
 * @param status exit status
 */
extern void eel_exit(int status);

/**
 * @brief Checks the eel_exit() call status flag
 *
 * @return true
 * @return false
 */
extern bool eel_exit_called(void);

/**
 * @brief Clears the eel_exit() call status flag
 *
 */
extern void eel_exit_called_clear(void);

/**
 * @brief Sets the eel_exit() call expected flag
 *
 */
extern void eel_exit_expected_set(void);

/**
 * @brief Clears the eel_exit() call expected flag
 *
 */
extern void eel_exit_expected_clear(void);

/**
 * @brief Returns the status from the eel_exit() call
 *
 * @return int the exit status
 */
extern int eel_exit_status(void);

#endif
