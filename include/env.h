#ifndef JISP_ENV_H_
#define JISP_ENV_H_
#include <fmt/format.h>

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class BaseValue;
class Env;


class Env {
using Func = std::function<std::unique_ptr<BaseValue>(
    std::unique_ptr<Env>, std::unique_ptr<BaseValue>)>;
 public:
  void add_builtin(const std::string& name,
                   Func func);  // add builtins by using lambdas???
  std::unordered_map<std::string, std::unique_ptr<Func>> envs;
};
#endif
