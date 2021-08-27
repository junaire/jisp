#include "jisp/parser.h"

ValuePtr Parser::parse() {
  for (auto& token : tokens) {
    if (token.getType() == TokenType::NUMBER)
      return std::make_unique<NumberValue>(token.getValue());
  }
  return nullptr;
}
