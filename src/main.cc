#include <fmt/format.h>

#include <fstream>
#include <string_view>

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"
#include "jisp/ast/visitor.h"
#include "jisp/env.h"
#include "jisp/lexer/lexer.h"
#include "jisp/parser/parser.h"

void banner() {
  fmt::print("Jun's own Lisp\n");
  fmt::print("Version v0.0.1\n");
}

std::string readFile(const char* name) {
  std::ifstream file{name};
  std::string contents{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};
  return contents;
}

bool checkFileExtension(std::string_view name) {
  bool res = false;
  if (name.ends_with(".jun")) {
    res = true;
  }
  return res;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    banner();

    // TODO(Jun): Implement this
    fmt::print("Sorry but we don't have interpreter mode now :-(");
    return -1;
  }
  if (argc == 2) {
    const auto* file = argv[1];
    if (!checkFileExtension(file)) {
      fmt::print("The Jisp file must have `.jun` extension!\n");
      fmt::print("For exmaple: \n");
      fmt::print("$ jisp awesome.jun\n");
      return -1;
    }

    auto globalEnv = std::make_unique<Env>(nullptr);
    Visitor visitor{globalEnv.get()};

    Lexer lexer{readFile(file)};
    Parser parser{lexer.tokenize()};
    auto result = parser.parse()->exec(visitor);
    result.print();

  } else {
    fmt::print("Error arguments\n");
  }
}
