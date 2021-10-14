#ifndef JISP_LAMBDA_H_
#define JISP_LAMBDA_H_

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include "jisp/env.h"
#include "jisp/types.h"
#include "jisp/value.h"

class LambdaValue final : public Value {
 public:
  LambdaValue(std::unique_ptr<Value> f, std::unique_ptr<Value> b, Env* par)
      : formals(std::move(f)),
        body(std::move(b)),
        Value(ValueType::LAMBDA),
        // create a new environment
        env(std::make_shared<Env>(par)){};

  std::string inspect() override { return "<lambda>"; };
  std::unique_ptr<Value> accept(ASTVisitor& visitor) override;
  [[nodiscard]] bool isLiteral() const override { return false; }
  SexprValue* getFormals() { return formals->toSexpr(); }
  SexprValue* getBody() { return body->toSexpr(); }

  std::unique_ptr<Value> clone() override {
    return std::make_unique<LambdaValue>(formals->clone(), body->clone(),
                                         env.get());
  }
  void setFormals(std::string name, std::unique_ptr<Value> val) {
    env->set(std::move(name), std::move(val));
  }

  std::unique_ptr<Value> eval();

 private:
  std::shared_ptr<Env> env;
  std::unique_ptr<Value> formals;
  std::unique_ptr<Value> body;
};
#endif
