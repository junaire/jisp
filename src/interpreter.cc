#include "jisp/interpreter.h"

ValuePtr Interpreter::eval() {
  if (ast->getType() == Types::NUMBER) return ast;
  return nullptr;
}
