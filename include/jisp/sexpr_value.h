#ifndef JISP_SEXPR_VALUE_H_
#define JISP_SEXPR_VALUE_H_

#include <cassert>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class SexprValue final : public Value {
 public:
  SexprValue(Types type) : Value(type) {}
  void inspect() override{};
  void push(ValuePtr val) { elements.push_back(std::move(val)); }
  ValuePtr operator[](size_t idx) {
    assert(idx < elements.size());
    return elements[idx];
  }

 private:
  std::vector<ValuePtr> elements;
};
#endif
