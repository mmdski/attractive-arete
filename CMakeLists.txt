cmake_minimum_required(VERSION 3.18)

project(elated-eel)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
  add_compile_options(/guard:cf /analyze /permissive- /W4 /WX)

else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)

  if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
  endif()
endif()

if(TESTS)
  enable_testing()
  add_compile_definitions(TESTING)
endif()

# set check arguments
add_compile_definitions(CHECK_ARGS)

include_directories(include)

add_subdirectory(src)

macro(add_eel_exe basename)
  add_executable(${basename} ${basename}.c)
  target_link_libraries(${basename} PRIVATE eel)
endmacro()

# if(APP)
# add_subdirectory(app)
# endif()
if(TESTS)
  add_subdirectory(tests)
endif()
