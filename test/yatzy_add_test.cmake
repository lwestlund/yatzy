function(yatzy_add_test)
  set(options)
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES EXTRA_INCLUDES)
  cmake_parse_arguments("TEST" "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN})

  add_executable(${TEST_NAME} ${TEST_SOURCES})
  target_include_directories(${TEST_NAME} PRIVATE ${TEST_EXTRA_INCLUDES})
  target_link_libraries(${TEST_NAME} doctest)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

  add_dependencies(tests ${TEST_NAME})
endfunction()
