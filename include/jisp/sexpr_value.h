#ifndef JISP_SEXPR_VALUE_H_
#define JISP_SEXPR_VALUE_H_

#include <cassert>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class SexprValue final : public Value {
  using SexprSize = std::vector<ValuePtr>::size_type;

 public:
  explicit SexprValue(Types type) : Value(type) {}
  void inspect() override{};
  void push(ValuePtr val) { elements.push_back(std::move(val)); }
  ValuePtr operator[](size_t idx) {
    assert(idx < elements.size());
    return elements[idx];
  }
  [[nodiscard]] SexprSize size() const { return elements.size(); }
  ValuePtr pop(size_t idx) {
    assert(idx < elements.size());
    auto popEle = elements[idx];
    elements.erase(elements.begin() + idx);
    return popEle;
  }

 private:
  std::vector<ValuePtr> elements;
};
#endif
