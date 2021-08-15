cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(jisp)
# add_subdirectory(third-party/google-test)
SET(SOURCES
	src/envs.cc
	src/types.cc
	src/main.cc
)
find_package(fmt)

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
