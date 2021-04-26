add_custom_target(tests)
include(yatzy_add_test.cmake)

yatzy_add_test(
  NAME
  dice_set_tests
  SOURCES
  dice_set_tests.cpp
  ../src/dice_set.cpp
  EXTRA_INCLUDES
  ../src)

yatzy_add_test(
  NAME
  player_tests
  SOURCES
  player_tests.cpp
  ../src/player.cpp
  ../src/io.cpp
  ../src/dice_set.cpp
  EXTRA_INCLUDES
  ../src)
