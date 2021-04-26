cmake_minimum_required(VERSION 3.16)

project(Yatzy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_compile_options(
  -Wall
  -Wextra
  -Werror
  -Wconversion
  -Wold-style-cast
  -Wredundant-decls
  -Wshadow
  -Wcast-qual
  -Wformat=2
  -Wswitch-default
  -Wmissing-include-dirs
  -Wctor-dtor-privacy
  -Wdisabled-optimization
  -Weffc++
  -Wmissing-declarations
  -pedantic-errors
  -Wsign-conversion
  -Wswitch-enum)

if(${CMAKE_CXX_COMPILER} STREQUAL "g++")
  add_compile_options(-Wuseless-cast -Wduplicated-cond -Wduplicated-branches
                      -Wlogical-op)
endif()

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(test)
