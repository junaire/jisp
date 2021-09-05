#ifndef JISP_LEXER_H_
#define JISP_LEXER_H_

#include <optional>
#include <string>
#include <vector>

#include "jisp/token.h"
using Tokens = std::vector<Token>;

class Lexer {
 public:
  explicit Lexer(const std::string& input)
      : code(input), position(0), length(input.length()) {}
  Tokens tokenize();

 private:
  std::optional<Token> lex(const std::string& input);
  std::optional<Token> lexNumber(const std::string& input);
  std::optional<Token> lexSymbol(const std::string& input);
  std::optional<Token> lexString(const std::string& input);
  std::optional<Token> lexSyntax(const std::string& input);
  std::optional<Token> lexOperator(const std::string& input);

  void skipWhiteSpace();
  void advance();
  std::string code;
  size_t position;
  size_t length;
};
#endif
