#ifndef TYPES_H_
#define TYPES_H_
#include <fmt/format.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum { NUMBER, STRING, SYMBOL, ERROR };

class BaseValue {
 public:
  explicit BaseValue(const std::string& val) : value(val) {}
  std::string value;
};

class NumberValue : public BaseValue {
 public:
  explicit NumberValue(const std::string& val) : BaseValue(val) {}
};

class StringValue : public BaseValue {
 public:
  StringValue(const std::string& val) : BaseValue(val) {}
};
#endif
