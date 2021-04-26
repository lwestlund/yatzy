# doctest
add_library(
  doctest
  doctest/doctest_main.cpp
)
target_include_directories(
  doctest
  PUBLIC doctest/include
)
