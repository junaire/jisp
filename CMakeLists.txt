cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
project(jisp)

find_package(GTest REQUIRED)
find_package(fmt REQUIRED)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET(SOURCES
	src/env.cc
	src/types.cc
	src/main.cc
	src/tokenizer.cc
	src/lexer.cc
	src/interpreter.cc
)

add_executable(
	jisp
	${SOURCES}
)
target_include_directories(
	jisp
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
	jisp
	PRIVATE
	fmt::fmt
)

enable_testing()

add_executable(
	test_jisp
	tests/test_jisp.cc
	src/env.cc
	src/lexer.cc
	src/types.cc
	src/tokenizer.cc
	src/interpreter.cc
)

target_include_directories(
	test_jisp
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
	test_jisp
	PRIVATE
	fmt::fmt
	GTest::GTest
	GTest::Main
)

add_test(test_all test_jisp)
