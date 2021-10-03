#include <iostream>

#include "jisp/ast_visitor.h"
#include "jisp/builtin.h"
#include "jisp/env.h"
#include "jisp/lexer.h"
#include "jisp/parser.h"
#include "jisp/sexpr_value.h"
#include "linenoise.hpp"

int main() {
  const auto* path = "history.txt";
  // Load history
  linenoise::LoadHistory(path);

  // global environment
  auto env = std::make_shared<Env>(nullptr);
  auto visitor = ASTVisitor(env);

  fmt::print("Jun's own Lisp\n");

  while (true) {
    // Read line
    std::string line;
    auto quit = linenoise::Readline("Jisp> ", line);

    if (quit) {
      break;
    }

    auto lexer = Lexer(line);

    auto parser = Parser(lexer.tokenize());

    auto result = parser.parse()->accept(visitor);

    if (result->isSexpr()) {
      if (result->toSexpr()->size() != 0) {
        std::cout << result->inspect() << "\n";
      }
    } else {
      std::cout << result->inspect() << "\n";
    }

    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

