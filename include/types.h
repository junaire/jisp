#ifndef JISP_TYPES_H_
#define JISP_TYPES_H_

#include <fmt/format.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "env.h"

enum class Types { NUMBER, STRING, SYMBOL, ERROR, SEXPR, FUNCTION };

class BaseValue {
 public:
  virtual void add(std::shared_ptr<BaseValue>) = 0;
  [[maybe_unused]] virtual std::string getName() = 0;
  [[maybe_unused]] virtual std::shared_ptr<BaseValue> getValue() = 0;
  [[maybe_unused]] virtual Types getType() = 0;
  virtual ~BaseValue() = default;
};

class Literal : public BaseValue {
 public:
  Literal(Types tp, const std::string& val) : type(tp), value(val) {}
  std::string getName() override { return value; }
  Types getType() override { return type; }
  void add(std::shared_ptr<BaseValue>) override{};
  std::shared_ptr<BaseValue> getValue() override { return nullptr; }
  std::string value;

 private:
  Types type;
};

class Symbol : public BaseValue {
 public:
  Symbol(Types tp, const std::string& name, std::unique_ptr<BaseValue> val)
      : type(tp), name(name), value(std::move(val)) {}
  std::string getName() override { return name; }
  std::shared_ptr<BaseValue> getValue() override { return value; }
  void add(std::shared_ptr<BaseValue>) override{};
  Types getType() override { return type; }

 private:
  Types type;
  std::string name;
  std::shared_ptr<BaseValue> value;
};

class Function : public BaseValue {
  // change unique_ptr to shared_ptr
  using Func = std::function<std::unique_ptr<BaseValue>(
      std::unique_ptr<Env>, std::unique_ptr<BaseValue>)>;

 public:
  Function(Types tp, const std::string& name, Func f)
      : type(tp), name(name), func(std::move(f)) {}
  std::string getName() override { return name; }
  std::shared_ptr<BaseValue> getValue() override { return nullptr; }
  Types getType() override { return type; }
  void add(std::shared_ptr<BaseValue>) override{};

 private:
  std::string name;
  // should it be ptr?
  Func func;
  Types type;
};

class Sexpr : public BaseValue {
 public:
  explicit Sexpr(Types tp) : type(tp) {}
  void add(std::shared_ptr<BaseValue> val) override;
  std::shared_ptr<BaseValue> getValue() override { return nullptr; }
  Types getType() override { return type; }
  std::string getName() override { return "<Sexpr>"; }

  std::vector<std::shared_ptr<BaseValue>> expr;

 private:
  Types type;
};

#endif
