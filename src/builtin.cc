#include "jisp/ast/builtin.h"

#include <fmt/format.h>

#include <cassert>

#include "jisp/ast/ast.h"
#include "jisp/ast/visitor.h"
#include "jisp/value/value.h"

Value Add::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(!args.empty());
  int res = 0;
  for (const auto& arg : args) {
    res += arg->exec(visitor).toNumber();
  }
  return Value(res);
}

Value Sub::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(!args.empty());
  auto beg = args.begin();
  int res = (*beg++)->exec(visitor).toNumber();
  for (; beg != args.cend(); beg++) {
    res -= (*beg)->exec(visitor).toNumber();
  }
  return Value(res);
}

Value Multiply::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  int res = 1;
  for (const auto& arg : args) {
    res *= arg->exec(visitor).toNumber();
  }
  return Value(res);
}

Value Divide::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(!args.empty());
  auto beg = args.cbegin();
  int res = (*beg++)->exec(visitor).toNumber();
  assert(res != 0);
  for (; beg != args.cend(); beg++) {
    res /= (*beg)->exec(visitor).toNumber();
  }
  return Value(res);
}

Value Greater::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs > rhs);
}

Value Less::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs < rhs);
}

Value GreaterEqual::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs >= rhs);
}

Value LessEqual::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs <= rhs);
}

Value Equal::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs == rhs);
}

Value NotEqual::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto lhs = args[0]->exec(visitor).toNumber();
  auto rhs = args[1]->exec(visitor).toNumber();

  return Value(lhs != rhs);
}

Value And::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto lhs = args[0]->exec(visitor).toBoolean();
  auto rhs = args[1]->exec(visitor).toBoolean();

  return Value(lhs && rhs);
}

Value Or::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto lhs = args[0]->exec(visitor).toBoolean();
  auto rhs = args[1]->exec(visitor).toBoolean();

  return Value(lhs || rhs);
}

Value AddAssign::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto* lhs = args[0];
  auto res =
      args[0]->exec(visitor).toNumber() + args[1]->exec(visitor).toNumber();

  visitor.get(lhs->toIdentifier()->name())->toLiteral()->reset(Value(res));

  return Value();
}

Value SubAssign::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto* lhs = args[0];
  auto res =
      args[0]->exec(visitor).toNumber() - args[1]->exec(visitor).toNumber();
  visitor.get(lhs->toIdentifier()->name())->toLiteral()->reset(Value(res));

  return Value();
}
Value MultiplyAssgin::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto* lhs = args[0];
  auto res =
      args[0]->exec(visitor).toNumber() * args[1]->exec(visitor).toNumber();
  visitor.get(lhs->toIdentifier()->name())->toLiteral()->reset(Value(res));

  return Value();
}
Value DivideAssign::apply(Visitor& visitor, std::vector<ASTNode*>& args) {
  assert(args.size() == 2);

  auto* lhs = args[0];
  auto res =
      args[0]->exec(visitor).toNumber() / args[1]->exec(visitor).toNumber();
  visitor.get(lhs->toIdentifier()->name())->toLiteral()->reset(Value(res));

  return Value();
}
