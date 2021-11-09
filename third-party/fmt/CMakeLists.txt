configure_file(CMakeLists.txt.in fmt/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fmt )
if(result)
  message(FATAL_ERROR "CMake step for fmt failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fmt )
if(result)
  message(FATAL_ERROR "Build step for fmt failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/fmt-src
                 ${CMAKE_CURRENT_BINARY_DIR}/fmt-build)

