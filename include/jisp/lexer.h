#ifndef JISP_LEXER_H_
#define JISP_LEXER_H_

#include <string>
#include <vector>

#include "jisp/token.h"

using Tokens = std::vector<Token>;

class Lexer {
 public:
  Lexer(std::string input) : code(input), position(0), length(input.length()) {}
  Tokens tokenize();
  // is_*()
 private:
  Token next(char tok);
  void advance() { ++position; };
  char peek() { return code[position]; };
  std::string code;
  int position;
  int length;
};
#endif
