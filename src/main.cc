#include <fmt/format.h>

#include <fstream>

#include "jisp/ast/ast.h"
#include "jisp/ast/builtin.h"
#include "jisp/ast/visitor.h"
#include "jisp/env.h"
#include "jisp/lexer/lexer.h"
#include "jisp/parser/parser.h"

int main(int argc, char** argv) {
  auto env = std::make_unique<Env>(nullptr);
  auto visitor = Visitor(env.get());

  const char* contents = R"(
      "(fn func[a b] ( if (a) (* a b) ( + a b))) (func(1 5)))";
  /*
  std::ifstream file{argv[1]};
  std::string contents{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};

  */
  auto lexer = Lexer(std::move(contents));

  auto parser = Parser(lexer.tokenize());

  auto result = parser.parse()->exec(visitor);

  result.print();
}
