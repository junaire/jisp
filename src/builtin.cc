#include "jisp/ast/builtin.h"

#include <fmt/format.h>

#include <cassert>

#include "jisp/ast/ast.h"
#include "jisp/ast/visitor.h"
#include "jisp/value/value.h"

Value Add::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(!args.empty());
  int res = 0;
  for (const auto& arg : args) {
    res += arg.toNumber();
  }
  return Value(res);
}

Value Sub::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(!args.empty());
  auto beg = args.cbegin();
  int res = (beg++)->toNumber();
  for (; beg != args.cend(); beg++) {
    res -= beg->toNumber();
  }
  return Value(res);
}

Value Multiply::apply(Visitor& visitor, std::vector<Value>& args) {
  int res = 1;
  for (const auto& arg : args) {
    res *= arg.toNumber();
  }
  return Value(res);
}

Value Divide::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(!args.empty());
  auto beg = args.cbegin();
  int res = (beg++)->toNumber();
  assert(res != 0);
  for (; beg != args.cend(); beg++) {
    res /= beg->toNumber();
  }
  return Value(res);
}

Value Greater::apply(Visitor& visitor, std::vector<Value>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs > rhs);
}

Value Less::apply(Visitor& visitor, std::vector<Value>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs < rhs);
}

Value GreaterEqual::apply(Visitor& visitor, std::vector<Value>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs >= rhs);
}

Value LessEqual::apply(Visitor& visitor, std::vector<Value>& args) {
  if (args.size() != 2) {
    assert(false);
  }

  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs <= rhs);
}

Value Equal::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(args.size() == 2);

  // TODO(Jun): let Value return the variant, and use std::visit()
  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs == rhs);
}

Value NotEqual::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(args.size() == 2);

  auto lhs = args[0].toNumber();
  auto rhs = args[1].toNumber();

  return Value(lhs != rhs);
}

Value And::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(args.size() == 2);

  auto lhs = args[0].toBoolean();
  auto rhs = args[1].toBoolean();

  return Value(lhs && rhs);
}

Value Or::apply(Visitor& visitor, std::vector<Value>& args) {
  assert(args.size() == 2);

  auto lhs = args[0].toBoolean();
  auto rhs = args[1].toBoolean();

  return Value(lhs || rhs);
}
