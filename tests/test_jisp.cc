#include <gtest/gtest.h>

#include "jisp/interpreter.h"
#include "jisp/lexer.h"
#include "jisp/parser.h"

TEST(JispTest, LexerTest) {
  auto lexer = Lexer("( + 1 ( - 2 3))");
  auto tokens = lexer.tokenize();
  EXPECT_EQ("(", tokens[0].getValue());
  EXPECT_EQ("+", tokens[1].getValue());
  EXPECT_EQ("1", tokens[2].getValue());
  EXPECT_EQ("(", tokens[3].getValue());
  EXPECT_EQ("-", tokens[4].getValue());
  EXPECT_EQ("2", tokens[5].getValue());
  EXPECT_EQ("3", tokens[6].getValue());
  EXPECT_EQ(")", tokens[7].getValue());
  EXPECT_EQ(")", tokens[8].getValue());
}

/*
TEST(JispTest, ParserTest) {
  auto lexer = Lexer("1");
  auto tokens = lexer.tokenize();
  auto parser = Parser(tokens);
  auto ast = parser.parse();
  EXPECT_EQ("1", std::to_string(
                     std::dynamic_pointer_cast<NumberValue>(ast)->getValue()));
}

TEST(JispTest, InterpreterTest) {}
*/
