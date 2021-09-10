#include "jisp/parser.h"

#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/string_value.h"
#include "jisp/symbol_value.h"

ValuePtr Parser::parse() {
  while (index < tokens.size()) {
    return parseValue();
  }
  return nullptr;
}

ValuePtr Parser::parseValue() {
  auto token = tokens[index++];
  switch (token.getType()) {
    case TokenType::NUMBER:
      return std::make_unique<NumberValue>(token);
    case TokenType::STRING:
      return std::make_unique<StringValue>(token);
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::MULTIPLY:
    case TokenType::DIVIDE:
    case TokenType::SYMBOL:
      return std::make_unique<SymbolValue>(token);
    case TokenType::LBRACKET:
      return parseSexpr();
  }
  return nullptr;
}

ValuePtr Parser::parseSexpr() {
  auto sexpr = std::make_unique<SexprValue>(Types::SEXPR);
  while (tokens[index].getType() != TokenType::RBRACKET) {
    sexpr->push(parseValue());
  }

  return sexpr;
}
