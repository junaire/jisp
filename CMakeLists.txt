cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

# Give me warnings as much as possible
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wnon-virtual-dtor -pedantic -Wcast-align -Wnull-dereference")

# We don't use exceptions and RTTI
set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti")

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
