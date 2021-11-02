#ifndef JISP_LEXER_H_
#define JISP_LEXER_H_

#include <optional>
#include <string>
#include <vector>

#include "jisp/token.h"
using Tokens = std::vector<Token>;

class Lexer {
 public:
  explicit Lexer(std::string input) : input_(std::move(input)), position(0) {}
  Tokens tokenize();
  std::optional<Token> next();

 private:
  Token number();
  Token identifier();
  Token str();
  Token atom(Token::Kind kind);

  void skipWhiteSpace();
  void advance();
  char peek();
  char get();

  [[nodiscard]] static bool isValidChar(char c);

  std::string input_;
  size_t position;
};
#endif
