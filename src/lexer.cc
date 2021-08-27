#include "jisp/lexer.h"

Tokens Lexer::tokenize() {
  std::vector<Token> tokens;

  while (position < length) {
    auto current = code[position];
    tokens.push_back(next(current));
  }
  return tokens;
}

Token Lexer::next(char tok) {
  std::string token;
  if (std::isdigit(tok)) {
    token = tok;
  }
  advance();
  return Token(TokenType::NUMBER, token);
}

