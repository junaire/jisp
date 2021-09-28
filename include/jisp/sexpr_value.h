#ifndef JISP_SEXPR_VALUE_H_
#define JISP_SEXPR_VALUE_H_

#include <vector>

#include "jisp/token.h"
#include "jisp/value.h"

class SexprValue : public Value {
 public:
  explicit SexprValue() = default;
  std::string inspect() override {
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

  [[nodiscard]] auto size() const { return elements.size(); }

  Value* at(size_t idx) { return elements[idx].get(); }

  std::unique_ptr<Value>& get(size_t idx) { return elements[idx]; }

  std::vector<std::unique_ptr<Value>> elements;
};
#endif
