#ifndef JISP_TOKEN_H_
#define JISP_TOKEN_H_

#include <string>

#include "jisp/types.h"
class Token {
 public:
  Token() = default;
  Token(TokenType type, std::string value)
      : type(type), value(std::move(value)) {}
  std::string getValue() { return value; }
  TokenType getType() { return type; }

 private:
  std::string value;
  TokenType type;
};
#endif
