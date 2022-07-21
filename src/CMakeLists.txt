add_library(eel
  error.c
  exit.c
  memory.c
  posix.c
)

if(NOT MSVC)
  target_link_libraries(eel PRIVATE m)
endif()
