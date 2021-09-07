#include "jisp/interpreter.h"
#include "jisp/lexer.h"
#include "jisp/number_value.h"
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

    auto interpreter = Interpreter(parser.parse());
    auto result = interpreter.eval();
    if (result->getType() == Types::NUMBER) result->inspect();

    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

