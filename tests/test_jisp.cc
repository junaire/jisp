#include <gtest/gtest.h>

#include <string>

#include "jisp/builtin.h"
#include "jisp/env.h"
#include "jisp/interpreter.h"
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
  auto lexer = Lexer("(+1 (- 244 3))");
  auto tokens = lexer.tokenize();
  auto parser = Parser(tokens);
  auto ast = parser.parse();
  auto sexpr = std::dynamic_pointer_cast<SexprValue>(ast);

  auto tmp1 = std::dynamic_pointer_cast<SymbolValue>((*sexpr)[0]);
  EXPECT_EQ("+", tmp1->getName());

  auto tmp2 = std::dynamic_pointer_cast<NumberValue>((*sexpr)[1]);
  EXPECT_EQ("1", std::to_string(tmp2->getValue()));

  auto tmp4 = std::dynamic_pointer_cast<SexprValue>((*sexpr)[2]);

  auto tmp5 = std::dynamic_pointer_cast<SymbolValue>((*tmp4)[0]);
  EXPECT_EQ("-", tmp5->getName());

  auto tmp6 = std::dynamic_pointer_cast<NumberValue>((*tmp4)[1]);
  EXPECT_EQ("244", std::to_string(tmp6->getValue()));

  auto tmp7 = std::dynamic_pointer_cast<NumberValue>((*tmp4)[2]);
  EXPECT_EQ("3", std::to_string(tmp7->getValue()));
}

TEST(JispTest, EnvTest) {
  Env env;
  add_builtins(env);
  EXPECT_EQ(Types::FUNCTION, env.get("+")->getType());
  EXPECT_EQ(Types::FUNCTION, env.get("-")->getType());
  EXPECT_EQ(Types::FUNCTION, env.get("*")->getType());
  EXPECT_EQ(Types::FUNCTION, env.get("/")->getType());
}

TEST(JispTest, InterpreterTest) {
  auto lexer = Lexer("( + 1 2)");
  auto parser = Parser(lexer.tokenize());
  Env env;
  add_builtins(env);
  auto interpreter = Interpreter(parser.parse(), env);
  EXPECT_EQ("3", std::to_string(
                     std::dynamic_pointer_cast<NumberValue>(interpreter.eval())
                         ->getValue()));
}
