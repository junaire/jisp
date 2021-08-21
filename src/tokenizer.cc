#include "tokenizer.h"

// if only number, string return them directly
// else first create a sexpr, and push them in
std::vector<std::string> Tokenizer::tokenize() {
  std::vector<std::string> tokens;
  // parse the input, return tokens;
  // TODO: We should deal with strings
  for (auto& ch : input) {
    if (ch == '(' || ch == ')') {
      lastChar = ch;
      tokens.push_back(std::string(1, ch));
    } else if (std::isspace(ch)) {
      lastChar = ch;
      continue;
    } else if (std::isdigit(ch)) {
      if (std::isdigit(lastChar)) {
        tokens.back() += ch;
      } else {
        tokens.push_back(std::string(1, ch));
      }
      lastChar = ch;
    } else if (std::isalpha(ch)) {
      if (std::isalpha(lastChar)) {
        tokens.back() += ch;
      } else {
        tokens.push_back(std::string(1, ch));
      }
      lastChar = ch;
    } else {
      // TODO: Maybe we can deal with builtin functions like `head`, `+`, `def`
      lastChar = ch;
      tokens.push_back(std::string(1, ch));
    }
  }

  return tokens;
}
