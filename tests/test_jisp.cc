#include <gtest/gtest.h>

#include "jisp/interpreter.h"
#include "jisp/lexer.h"
#include "jisp/parser.h"

TEST(JispTest, LexerTest) {
  auto lexer = Lexer("1");
  auto tokens = lexer.tokenize();
  EXPECT_EQ("1", tokens[0].getValue());
}

TEST(JispTest, ParserTest) {
  auto lexer = Lexer("1");
  auto tokens = lexer.tokenize();
  auto parser = Parser(tokens);
  auto ast = parser.parse();
  EXPECT_EQ("1", std::to_string(
                     std::dynamic_pointer_cast<NumberValue>(ast)->getValue()));
}

TEST(JispTest, InterpreterTest) {}
