#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool expected = false;
bool called   = false;
int  status;

void
eel_exit_expected_set(void) {
  expected = true;
}

void
eel_exit_expected_clear(void) {
  expected = false;
}

void
eel_exit(int exit_status) {
  if (expected) {
    puts("Caught expected call to eel_exit()");
    called = true;
    status = exit_status;
  } else if (called) {
    fputs("Fatal Error: eel_exit() call flag already set", stderr);
    exit(EXIT_FAILURE);
  } else {
    fputs("Fatal Error: Unexpected call to eel_exit()\n", stderr);
    exit(exit_status);
  }
}

bool
eel_exit_called(void) {
  return called;
}

void
eel_exit_called_clear(void) {
  called = false;
}

int
eel_exit_status(void) {
  return status;
}
