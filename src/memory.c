#include <stdlib.h>

void *
eel_alloc(size_t nbytes) {
  return malloc(nbytes);
}

void *
eel_calloc(size_t count, size_t nbytes) {
  return calloc(count, nbytes);
}

void
eel_free(void *ptr) {
  free(ptr);
}
