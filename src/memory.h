#ifndef __MEM_H__
#define __MEM_H__

#include <stdlib.h>

extern void *eel_alloc(size_t nbytes);
extern void *eel_calloc(size_t count, size_t nbytes);
extern void  eel_free(void *ptr);

#define ALLOC(nbytes) eel_alloc((nbytes))
#define NEW(p) ((p) = ALLOC(sizeof *(p)))
#define FREE(ptr) ((void) (eel_free((ptr)), (ptr) = 0))

#endif
