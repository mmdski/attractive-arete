#ifndef __ERROR_H__
#define __ERROR_H__
#include <stdlib.h>

#define RAISE_NULL_ERR_INT                                                     \
  {                                                                            \
    eel_err_raise(NULL_ARGUMENT_ERROR, NULL, __FILE__, __LINE__);              \
    return NULL_ARGUMENT_ERROR;                                                \
  }

#define RAISE_NULL_ERR_NULL                                                    \
  {                                                                            \
    eel_err_raise(NULL_ARGUMENT_ERROR, NULL, __FILE__, __LINE__);              \
    return NULL;                                                               \
  }

#define RAISE_ARG_ERR_INT                                                      \
  {                                                                            \
    eel_err_raise(INVALID_ARGUMENT_ERROR, NULL, __FILE__, __LINE__);           \
    return INVALID_ARGUMENT_ERROR;                                             \
  }

#define RAISE_ARG_ERR_NULL                                                     \
  {                                                                            \
    eel_err_raise(INVALID_ARGUMENT_ERROR, NULL, __FILE__, __LINE__);           \
    return NULL;                                                               \
  }

#endif
