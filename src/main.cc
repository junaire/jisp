#include "jisp/builtin.h"
#include "jisp/interpreter.h"
#include "jisp/lexer.h"
#include "jisp/parser.h"
#include "linenoise.hpp"

int main() {
  const auto path = "history.txt";
  // Load history
  linenoise::LoadHistory(path);

  while (true) {
    // Read line
    std::string line;
    auto quit = linenoise::Readline("Jisp> ", line);

    if (quit) {
      break;
    }

    auto lexer = Lexer(line);

    auto parser = Parser(lexer.tokenize());

    Env env;
    add_builtins(env);
    auto interpreter = Interpreter(parser.parse(), env);
    auto result = interpreter.eval();
    // We should write a helper function, like `jispPrint`
    if (result->getType() == Types::NUMBER) result->inspect();

    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

