#include <gtest/gtest.h>

#include <string>

#include "jisp/interpreter.h"
#include "jisp/lexer.h"
#include "jisp/number_value.h"
#include "jisp/parser.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"

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

TEST(JispTest, ParserTest) {
  auto lexer = Lexer("(+1 (- 2 3))");
  auto tokens = lexer.tokenize();
  auto parser = Parser(tokens);
  auto ast = parser.parse();
  auto sexpr = dynamic_cast<SexprValue*>(ast.get());

  auto tmp1 = dynamic_cast<SymbolValue*>((*sexpr)[0].get());
  EXPECT_EQ("+", tmp1->getName());

  auto tmp2 = dynamic_cast<NumberValue*>((*sexpr)[1].get());
  EXPECT_EQ("1", std::to_string(tmp2->getValue()));

  auto tmp4 = dynamic_cast<SexprValue*>((*sexpr)[2].get());

  auto tmp5 = dynamic_cast<SymbolValue*>((*tmp4)[0].get());
  EXPECT_EQ("-", tmp5->getName());

  auto tmp6 = dynamic_cast<NumberValue*>((*tmp4)[1].get());
  EXPECT_EQ("2", std::to_string(tmp6->getValue()));

  auto tmp7 = dynamic_cast<NumberValue*>((*tmp4)[2].get());
  EXPECT_EQ("3", std::to_string(tmp7->getValue()));
}

/*
TEST(JispTest, InterpreterTest) {}
*/
