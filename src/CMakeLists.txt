add_library(eel
  error.c
  exit.c
  memory.c
  string.c
)

if(NOT MSVC)
  target_link_libraries(eel PRIVATE m)
endif()
