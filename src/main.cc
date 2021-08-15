#include "env.h"
#include "linenoise.hpp"
#include "types.h"

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

	fmt::print("{}\n",line);
    // Add text to history
    linenoise::AddHistory(line.c_str());
  }
  // Save history
  linenoise::SaveHistory(path);
}

