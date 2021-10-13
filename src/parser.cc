#include "jisp/parser.h"

#include "jisp/builtin.h"
#include "jisp/function_value.h"
#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/string_value.h"
#include "jisp/symbol_value.h"
#include "jisp/types.h"

std::unique_ptr<Value> Parser::parse() {
  while (index < tokens.size()) {
    return parseValue();
  }
  return nullptr;
}

std::unique_ptr<Value> Parser::parseValue() {
  auto token = tokens[index++];
  switch (token.getType()) {
    case TokenType::NUMBER:
      return std::make_unique<NumberValue>(token.getValue());
    case TokenType::STRING:
      return std::make_unique<StringValue>(token.getValue());
    case TokenType::PLUS:
      return std::make_unique<FunctionValue>(
          "+", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "+"); });
    case TokenType::MINUS:
      return std::make_unique<FunctionValue>(
          "-", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "-"); });
    case TokenType::MULTIPLY:
      return std::make_unique<FunctionValue>(
          "*", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "*"); });
    case TokenType::DIVIDE:
      return std::make_unique<FunctionValue>(
          "/", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "/"); });
    case TokenType::PRINT:
      return std::make_unique<FunctionValue>(
          "print", true,
          [](Env& env, Value* vp) { return builtinPrint(env, vp); });
    case TokenType::DEFINE:
      return std::make_unique<FunctionValue>(
          "define", false,
          [](Env& env, Value* vp) { return builtinDefine(env, vp); });
    case TokenType::LAMBDA:
      // It is a builtin function, and it makes a lambda
      return std::make_unique<FunctionValue>(
          "lambda", false,
          [](Env& env, Value* vp) { return builtinLambda(env, vp); });
    case TokenType::SYMBOL:
      return std::make_unique<SymbolValue>(token.getValue());
    case TokenType::LBRACKET:
      return parseSexpr();
  }
  return nullptr;
}

std::unique_ptr<Value> Parser::parseSexpr() {
  auto sexpr = std::make_unique<SexprValue>();
  while (tokens[index].getType() != TokenType::RBRACKET) {
    sexpr->push(parseValue());
  }
  if (index < tokens.size()) {
    index++;
  }

  return sexpr;
}
