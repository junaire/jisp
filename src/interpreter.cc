#include "jisp/interpreter.h"

#include "jisp/function_value.h"
#include "jisp/sexpr_value.h"
#include "jisp/symbol_value.h"
#include "jisp/types.h"

ValuePtr Interpreter::eval() { return evalNode(ast); }

ValuePtr Interpreter::evalNode(ValuePtr node) {
  // eval symbols from environment
  switch (node->getType()) {
    case Types::STRING:
    case Types::NUMBER:
      return node;
    case Types::SYMBOL:
      return environment.get(
          std::dynamic_pointer_cast<SymbolValue>(node)->getName());
    case Types::SEXPR:
      return evalSexpr(node);
    case Types::LAMBDA:
    case Types::FUNCTION:
      return nullptr;
  }
}

ValuePtr Interpreter::evalSexpr(const ValuePtr& node) {
  // traverse the AST tree, call eval...
  auto sexpr = std::dynamic_pointer_cast<SexprValue>(node);

  auto result = std::make_shared<SexprValue>(Types::SEXPR);

  for (int i = 0; i < sexpr->size(); i++) {
    result->push(evalNode((*sexpr)[i]));
  }

  auto fun = result->pop(0);
  auto f = std::dynamic_pointer_cast<FunctionValue>(fun);
  return f->call(environment, std::move(result));
}
