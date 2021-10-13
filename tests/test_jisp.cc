#include <gtest/gtest.h>

#include <string>

#include "jisp/ast_visitor.h"
#include "jisp/builtin.h"
#include "jisp/env.h"
#include "jisp/function_value.h"
#include "jisp/lexer.h"
#include "jisp/number_value.h"
#include "jisp/parser.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"
#include "jisp/types.h"

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
  auto lexer = Lexer("(+1 (- 244 3) ( * 5 6))");
  auto tokens = lexer.tokenize();
  auto parser = Parser(tokens);
  auto ast = parser.parse();
  auto* sexpr = ast->toSexpr();

  EXPECT_EQ("+", sexpr->at(0)->toFunction()->getName());

  EXPECT_EQ("1", std::to_string(sexpr->at(1)->toNumber()->getValue()));

  auto* subSexpr1 = sexpr->at(2)->toSexpr();

  EXPECT_EQ("-", subSexpr1->at(0)->toFunction()->getName());

  EXPECT_EQ("244", std::to_string(subSexpr1->at(1)->toNumber()->getValue()));

  EXPECT_EQ("3", std::to_string(subSexpr1->at(2)->toNumber()->getValue()));

  auto* subSexpr2 = sexpr->at(3)->toSexpr();

  EXPECT_EQ("*", subSexpr2->at(0)->toFunction()->getName());
  EXPECT_EQ("5", std::to_string(subSexpr2->at(1)->toNumber()->getValue()));
  EXPECT_EQ("6", std::to_string(subSexpr2->at(2)->toNumber()->getValue()));
}

TEST(JispTest, ASTVisitorTest) {
  auto lexer = Lexer("( + 1 2)");
  auto parser = Parser(lexer.tokenize());
  auto visitor = ASTVisitor(std::make_unique<Env>(nullptr));
  auto result = parser.parse();
  EXPECT_EQ("3", result->accept(visitor)->inspect());
}
