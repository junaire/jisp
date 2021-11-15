#ifndef JISP_LEXER_H_
#define JISP_LEXER_H_

#include <string>
#include <vector>

#include "jisp/lexer/token.h"

using Tokens = std::vector<Token>;

class Lexer {
 public:
  explicit Lexer(std::string input) : input_(std::move(input)), position(0) {}
  Tokens tokenize();
  Token next();

 private:
  Token number();
  Token identifierOrKeyword();
  Token str();
  Token atom(Token::Kind kind);
  // This enable us to lex operators like `>=` , `<=` and etc
  Token op();

  void skipWhiteSpace();
  void advance();
  char peek();
  char get();

  [[nodiscard]] static bool isValidChar(char c);

  std::string input_;
  size_t position;
};
#endif
