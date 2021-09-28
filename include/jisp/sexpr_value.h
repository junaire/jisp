#ifndef JISP_SEXPR_VALUE_H_
#define JISP_SEXPR_VALUE_H_

#include <vector>

#include "jisp/token.h"
#include "jisp/types.h"
#include "jisp/value.h"

class SexprValue final : public Value {
 public:
  SexprValue() : Value(ValueType::SEXPR){};

  [[nodiscard]] auto size() const { return elements.size(); }

  std::string inspect() override {
    if (size() == 0) {
      return "";
    }

    std::string ouput{"( "};
    for (const auto& ele : elements) {
      ouput.append(ele->inspect());
      ouput.append(" ");
    }
    ouput.append(")");
    return ouput;
  };

  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;

  void push(std::unique_ptr<Value> val) { elements.push_back(std::move(val)); }

  std::unique_ptr<Value> pop(size_t idx) {
    auto popEle = std::move(elements[idx]);
    elements.erase(elements.begin() + idx);
    return popEle;
  }

  Value* at(size_t idx) { return elements[idx].get(); }

  std::unique_ptr<Value>& get(size_t idx) { return elements[idx]; }

  std::vector<std::unique_ptr<Value>> elements;
};
#endif
