#include <iostream>

#include "jisp/ast_visitor.h"
#include "jisp/builtin.h"
#include "jisp/lexer.h"
#include "jisp/parser.h"
#include "linenoise.hpp"

int main() {
  const auto* path = "history.txt";
  // Load history
  linenoise::LoadHistory(path);

  // global environment
  auto env = std::make_shared<Env>();
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

    auto result = parser.parse();
    std::cout << result->accept(visitor)->inspect() << "\n";

    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

