#include "jisp/interpreter.h"

#include "jisp/number_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"
#include "jisp/types.h"

ValuePtr Interpreter::eval() {
  if (ast->getType() == Types::NUMBER) return ast;
  if (ast->getType() == Types::SEXPR) {
    auto sexpr = std::dynamic_pointer_cast<SexprValue>(ast);

    auto op = std::dynamic_pointer_cast<SymbolValue>((*sexpr)[0]);

    if (op->getName() == "+") {
      auto result =
          std::dynamic_pointer_cast<NumberValue>((*sexpr)[1])->getValue() +
          std::dynamic_pointer_cast<NumberValue>((*sexpr)[2])->getValue();
      return std::make_shared<NumberValue>(std::to_string(result));
    }
  }
}
