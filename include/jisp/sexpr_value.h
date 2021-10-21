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

  [[nodiscard]] bool empty() const { return elements.empty(); }

  std::string inspect() override {
    if (empty()) {
      return "";
    }
    if (size() == 1) {
      return elements.at(0)->inspect();
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

  [[nodiscard]] bool isLiteral() const override {
    for (const auto& ele : elements) {
      if (!ele->isLiteral()) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] bool isPartLiteral(int idx) {
    for (; idx < size(); idx++) {
      if (!at(idx).isLiteral()) {
        return false;
      }
    }
    return true;
  }

  std::unique_ptr<Value> clone() override {
    auto newSexpr = std::make_unique<SexprValue>();
    for (auto& value : elements) {
      newSexpr->push(value->clone());
    }
    return newSexpr;
  }

  void push(std::unique_ptr<Value> val) { elements.push_back(std::move(val)); }

  // TODO(Jun): maybe we can use a better container to store elements
  std::unique_ptr<Value> pop(size_t idx) {
    auto popEle = std::move(elements[idx]);
    elements.erase(elements.begin() + idx);
    return popEle;
  }

  Value& at(size_t idx) { return *elements.at(idx); }

  std::vector<std::unique_ptr<Value>> elements;
};
#endif
