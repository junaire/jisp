#ifndef JISP_LEXER_H_
#define JISP_LEXER_H_

#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "jisp/token.h"
using Tokens = std::vector<Token>;

class Lexer {
 public:
  Lexer() = default;
  Tokens tokenize(std::string_view input);

 private:
  std::optional<Token> lex(std::string_view code);
  std::optional<Token> lexNumber(std::string_view code);
  std::optional<Token> lexSymbol(std::string_view code);
  std::optional<Token> lexString(std::string_view code);
  std::optional<Token> lexSyntax(std::string_view code);
  std::optional<Token> lexOperator(std::string_view code);

  void skipWhiteSpace(std::string_view code);
  void advance();
  size_t position;
  size_t length;
};
#endif
