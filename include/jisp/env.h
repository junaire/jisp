#ifndef JISP_ENV_H_
#define JISP_ENV_H_

#include <fmt/format.h>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "jisp/value.h"

class Env {
 public:
  explicit Env(Env* par) : parent(par){};

  Env() = default;
  ~Env() = default;

  /*
  Env(const Env&) = delete;
  Env& operator=(const Env&) = delete;
  Env(Env&&) = delete;
  Env& operator=(Env&&) = delete;
  */

  void set(std::string name, std::unique_ptr<Value> val) {
    // TODO(Jun): if we already have that symbol, we should update it instead of
    // creating a new one
    environment.emplace(std::make_pair(std::move(name), std::move(val)));
  }

  Value* get(const std::string& name) {
    // auto result = environment.find(name);
    auto result = environment.find(name);
    if (result != environment.end()) {
      return result->second.get();
    }
    return nullptr;
    // TODO(Jun): If we can't find the symbol, we should throw an error:
    // Unbound symbol
  }

  // Debug popurse
  void dump() {
    for (const auto& item : environment) {
      fmt::print("name = {}, value = {}\n", item.first, item.second->inspect());
    }
  }

  void setParent(Env* par) { parent = par; }

 private:
  std::unordered_map<std::string, std::unique_ptr<Value>> environment;
  Env* parent = nullptr;
};
#endif
