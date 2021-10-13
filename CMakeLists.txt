cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wnon-virtual-dtor -pedantic -Wcast-align -Wnull-dereference")
set(CMAKE_CXX_FLAGS "-fno-exceptions")
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(jisp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(third-party/google-test)
add_subdirectory(third-party/fmt)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
add_test(NAME test COMMAND ${CMAKE_BINARY_DIR}/bin/test_jisp)
