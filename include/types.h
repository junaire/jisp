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
  BaseValue(Types tp) : type(tp) {}
  Types getType() { return type; }
  virtual ~BaseValue() = default;

 private:
  Types type;
};

class Literal : public BaseValue {
 public:
  Literal(Types tp, std::string val) : BaseValue(tp), value(std::move(val)) {}
  std::string getValue() { return value; }

 private:
  std::string value;
};

class Symbol : public BaseValue {
 public:
  Symbol(Types tp, std::string name, std::unique_ptr<BaseValue> val)
      : BaseValue(tp), name(std::move(name)), value(std::move(val)) {}
  std::string getName() { return name; }
  std::shared_ptr<BaseValue> getValue() { return value; }

 private:
  std::string name;
  std::shared_ptr<BaseValue> value;
};

class Function : public BaseValue {
  // change unique_ptr to shared_ptr
  using Func = std::function<std::unique_ptr<BaseValue>(
      std::unique_ptr<Env>, std::unique_ptr<BaseValue>)>;

 public:
  Function(Types tp, std::string name, Func f)
      : BaseValue(tp), name(std::move(name)), func(std::move(f)) {}
  std::string getName() { return name; }

  Func func;

 private:
  std::string name;
};

class Sexpr : public BaseValue {
 public:
  explicit Sexpr(Types tp) : BaseValue(tp) {}
  void add(std::shared_ptr<BaseValue> val);
  std::vector<std::shared_ptr<BaseValue>> getValue();
  std::vector<std::shared_ptr<BaseValue>> expr;
};

#endif
