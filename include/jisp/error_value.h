#ifndef JISP_ERROR_VALUE_H_
#define JISP_ERROR_VALUE_H_

#include <fmt/format.h>

#include <memory>
#include <string>

#include "jisp/types.h"
#include "jisp/value.h"
class ErrorValue : public Value {
 public:
  explicit ErrorValue(std::string err)
      : errMsg(std::move(err)), Value(ValueType::ERROR) {}
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;
  std::string inspect() override { return fmt::format("Error: {}", errMsg); }
  [[nodiscard]] bool isLiteral() const override { return true; }
  std::unique_ptr<Value> clone() override {
    return std::make_unique<ErrorValue>(errMsg);
  }

 private:
  std::string errMsg;
};
#endif
