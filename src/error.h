#ifndef __ERROR_H__
#define __ERROR_H__
#include <stdlib.h>

#define RAISE_NULL_ERR_INT                                                     \
  {                                                                            \
    eel_err_raise(EEL_NULL_ARG_ERROR, NULL, __FILE__, __LINE__);               \
    return EEL_NULL_ARG_ERROR;                                                 \
  }

#define RAISE_NULL_ERR_NULL                                                    \
  {                                                                            \
    eel_err_raise(EEL_NULL_ARG_ERROR, NULL, __FILE__, __LINE__);               \
    return NULL;                                                               \
  }

#define RAISE_ARG_ERR_INT                                                      \
  {                                                                            \
    eel_err_raise(EEL_INVALID_ARG_ERROR, NULL, __FILE__, __LINE__);            \
    return EEL_INVALID_ARG_ERROR;                                              \
  }

#define RAISE_ARG_ERR_NULL                                                     \
  {                                                                            \
    eel_err_raise(EEL_INVALID_ARG_ERROR, NULL, __FILE__, __LINE__);            \
    return NULL;                                                               \
  }

#endif
