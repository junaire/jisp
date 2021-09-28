add_executable(
	test_jisp
	${PROJECT_SOURCE_DIR}/tests/test_jisp.cc
	${PROJECT_SOURCE_DIR}/src/lexer.cc
	${PROJECT_SOURCE_DIR}/src/parser.cc
	${PROJECT_SOURCE_DIR}/src/ast_visitor.cc
	${PROJECT_SOURCE_DIR}/src/builtin.cc
	${PROJECT_SOURCE_DIR}/src/value.cc
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

