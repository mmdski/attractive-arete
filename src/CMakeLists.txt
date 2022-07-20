add_library(eel
  exit.c
)

if(NOT MSVC)
  target_link_libraries(eel PRIVATE m)
endif()
