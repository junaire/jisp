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
  switch (token.getKind()) {
    case Token::Kind::Integer:
      return std::make_unique<NumberValue>(token.getValue());
    case Token::Kind::String:
      return std::make_unique<StringValue>(token.getValue());
    case Token::Kind::Plus:
      return std::make_unique<FunctionValue>(
          "+", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "+"); });
    case Token::Kind::Minus:
      return std::make_unique<FunctionValue>(
          "-", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "-"); });
    case Token::Kind::Multiply:
      return std::make_unique<FunctionValue>(
          "*", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "*"); });
    case Token::Kind::Divide:
      return std::make_unique<FunctionValue>(
          "/", true,
          [](Env& env, Value* vp) { return builtinOperators(env, vp, "/"); });
    case Token::Kind::Identifier:
      return std::make_unique<SymbolValue>(token.getValue());
    case Token::Kind::LeftParen:
      return parseSexpr();
  }
  return nullptr;
}

std::unique_ptr<Value> Parser::parseSexpr() {
  auto sexpr = std::make_unique<SexprValue>();
  while (tokens[index].getKind() != Token::Kind::RightParen) {
    sexpr->push(parseValue());
  }
  if (index < tokens.size()) {
    index++;
  }

  return sexpr;
}
