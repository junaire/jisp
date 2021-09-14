#ifndef JISP_ENV_H_
#define JISP_ENV_H_

#include <fmt/format.h>

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "jisp/value.h"

class Env {
 public:
  Env() = default;
  // Env(const Env&) = delete;
  // Env(Env&&) = default;
  void set(std::string name, ValuePtr val) {
    // TODO(Jun): if we already have that symbol, we should update it instead of
    // creating a new one
    environment.emplace(std::make_pair(std::move(name), std::move(val)));
  }

  ValuePtr get(const std::string& name) {
    // auto result = environment.find(name);
    auto result = environment.find(name);
    if (result != environment.end()) {
      return result->second;
    }
    std::terminate();
    // TODO(Jun): If we can't find the symbol, we should throw an error:
    // Unbound symbol
  }

  // Debug popurse
  void dump() {
    for (const auto& item : environment) {
      fmt::print("{} => ", item.first);
      item.second->inspect();
    }
  }

 private:
  std::unordered_map<std::string, ValuePtr> environment;
};
#endif
