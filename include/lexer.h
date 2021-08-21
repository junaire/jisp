#ifndef JISP_PARSER_H_
#define JISP_PARSER_H_

#include <memory>
#include <string>
#include <vector>
#include <list>

#include "types.h"

class Lexer {
  using Tokens = std::vector<std::string>;

 public:
  explicit Lexer(Tokens toks) : tokens(std::move(toks)){};
  std::shared_ptr<BaseValue> parse();  // interface of parse tokens

 private:
  static bool isNumber(const std::string& str);
  // FIXME: a symbol, a string, what should contain? what are invalid?
  // bool isCharacter(const std::string& str);
  std::vector<std::string> tokens;
};
#endif
