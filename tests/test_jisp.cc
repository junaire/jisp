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

std::string interpret(const std::string& str, ASTVisitor& visitor) {
  auto lexer = Lexer();
  auto parser = Parser(lexer.tokenize(str));
  auto result = parser.parse();
  return result->accept(visitor)->inspect();
}

TEST(LexerTest, EmptyInput) {
  auto lexer = Lexer();
  auto tokens = lexer.tokenize(" ");
  EXPECT_EQ(0, tokens.size());
}

TEST(LexerTest, SimpleArithmeticOperation) {
  auto lexer = Lexer();
  auto tokens = lexer.tokenize("( + 20 22 )");
  EXPECT_EQ("(", tokens[0].getValue());
  EXPECT_EQ("+", tokens[1].getValue());
  EXPECT_EQ("20", tokens[2].getValue());
  EXPECT_EQ("22", tokens[3].getValue());
  EXPECT_EQ(")", tokens[4].getValue());
}

TEST(LexerTest, ComplexArithmeticOperation) {
  auto lexer = Lexer();
  auto tokens = lexer.tokenize("( + 1 ( - 2 3))");
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

TEST(ParserTest, EchoBack) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);
  initBuiltins(*env);
  EXPECT_EQ("42", interpret("42", visitor));
  EXPECT_EQ("( 1 2 3 )", interpret("(1 2 3      )", visitor));
}

TEST(ParserTest, SimpleAddition) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);

  EXPECT_EQ("42", interpret("(+ 40 2)", visitor));
}

TEST(ParserTest, SimpleSubtraction) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);

  EXPECT_EQ("42", interpret("(- 48 6)", visitor));
}

TEST(ParserTest, SimpleMultiplication) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);

  EXPECT_EQ("42", interpret("(* 6 7)", visitor));
}

TEST(ParserTest, SimpleDivision) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);

  EXPECT_EQ("42", interpret("(/ 336 8)", visitor));
}

TEST(ParserTest, DefinSymbol) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);
  initBuiltins(*env);
  interpret("(define x 42)", visitor);
  EXPECT_EQ("42", interpret("x", visitor));
}

TEST(ParserTest, PrintTest) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);
  initBuiltins(*env);
  testing::internal::CaptureStdout();
  interpret("(print 42)", visitor);
  EXPECT_EQ("42", testing::internal::GetCapturedStdout());

  testing::internal::CaptureStdout();
  interpret("(print (* 6 7))", visitor);
  EXPECT_EQ("42", testing::internal::GetCapturedStdout());

  testing::internal::CaptureStdout();
  interpret("(define x 42)", visitor);
  interpret("(print x)", visitor);
  EXPECT_EQ("42", testing::internal::GetCapturedStdout());
}

TEST(ParserTest, LambdaTest) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);
  initBuiltins(*env);
  interpret("(define func (lambda (x y) (* x y)))", visitor);
  EXPECT_EQ("42", interpret("(func 21 2)", visitor));
}

TEST(ErrorTest, DivideByZeroTest) {
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);
  initBuiltins(*env);
  EXPECT_EQ("Error: Dividend can not be zero", interpret("(/ 0 42)", visitor));
}
