SET(SOURCES
	main.cc
	lexer.cc
	parser.cc
	builtin.cc
	ast_visitor.cc
	value.cc
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
