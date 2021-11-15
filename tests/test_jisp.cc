#include <gtest/gtest.h>

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"
#include "jisp/ast/visitor.h"
#include "jisp/env.h"
#include "jisp/lexer/lexer.h"
#include "jisp/lexer/token.h"
#include "jisp/parser/parser.h"
#include "jisp/value/value.h"

TEST(LexerTest, SimpleArithmeticOperation) {
  auto lexer = Lexer("( + 20 22 )");
  auto tokens = lexer.tokenize();
  EXPECT_EQ("(", tokens[0].getValue());
  EXPECT_EQ("+", tokens[1].getValue());
  EXPECT_EQ("20", tokens[2].getValue());
  EXPECT_EQ("22", tokens[3].getValue());
  EXPECT_EQ(")", tokens[4].getValue());
}

TEST(LexerTest, ComplexArithmeticOperation) {
  auto lexer = Lexer("( +1 ( - 2 3))    ");
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

TEST(LexerTest, String) {
  auto lexer = Lexer("\"This is a string\"");
  auto tokens = lexer.tokenize();
  EXPECT_EQ("This is a string", tokens[0].getValue());
}

std::string interpret(const std::string& input, Visitor& visitor) {
  Lexer lexer{input};
  Parser parser{lexer.tokenize()};
  return parser.parse()->exec(visitor).toString();
}

TEST(ParserTest, EchoBack) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());
  EXPECT_EQ("42", interpret("42", visitor));
  EXPECT_EQ("Hello", interpret("\"Hello\"", visitor));
}

TEST(ParserTest, SimpleAddition) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());

  EXPECT_EQ("42", interpret("(+ 40 2)  ", visitor));
}

TEST(ParserTest, SimpleSubtraction) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());

  EXPECT_EQ("42", interpret("(- 48 6)", visitor));
}

TEST(ParserTest, SimpleMultiplication) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());

  EXPECT_EQ("42", interpret("(* 6 7)", visitor));
}

TEST(ParserTest, SimpleDivision) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());

  EXPECT_EQ("42", interpret("(/ 336 8)", visitor));
}

TEST(ParserTest, DefinSymbol) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());
  EXPECT_EQ("42", interpret("(def x 42) (x)", visitor));
}

TEST(ParserTest, Function) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());
  EXPECT_EQ("42",
            interpret("(fn func [x] ( if (x) ( + x 1) ( * x 5))) (func (41))",
                      visitor));
}

TEST(ConditionTest, IfExpression) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());
  EXPECT_EQ("42", interpret("(if (1) (42) (24))", visitor));
  EXPECT_EQ("42", interpret("(if (0) (24) (42))", visitor));
  EXPECT_EQ("42",
            interpret("( def x 30) (if (x) ( + 30 12) ( -  x 56)) ", visitor));
}

TEST(LoopTest, WhileExpression) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());
  EXPECT_EQ(
      "42",
      interpret(
          "(def x 1) (def y 22) ( while ( <= x 10) ( ( += x 1) ( += y 2) y))",
          visitor));
}
