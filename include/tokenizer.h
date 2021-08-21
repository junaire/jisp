#ifndef JISP_TOKENIZER_H_
#define JISP_TOKENIZER_H_

#include <memory>
#include <string>
#include <vector>

class Tokenizer {
 public:
  explicit Tokenizer(const std::string& in) : input(in), lastChar(' ') {}
  std::vector<std::string> tokenize();

 private:
  std::string input;
  char lastChar;
};
#endif
