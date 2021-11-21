SET(SOURCES
	main.cc
	lexer.cc
	parser.cc
	env.cc
	builtin.cc
	ast.cc
	visitor.cc
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
	gflags::gflags
)
install (TARGETS jisp
    DESTINATION /usr/local/bin)