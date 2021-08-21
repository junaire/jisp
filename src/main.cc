#include "lexer.h"
#include "linenoise.hpp"
#include "tokenizer.h"

// Actual logic here
void exec(const std::string& line) {
  // read => eval => print
  Tokenizer tokenizer(line);
  auto tokens = tokenizer.tokenize();
  Lexer lexer(tokens);
  auto ast = lexer.parse();

  // We need parse it to AST tree
  // Now we have a vector of BaseValue ptrs;
  // Eval it
  // print it
}

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
    exec(line);

    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

