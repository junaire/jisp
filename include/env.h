#ifndef ENV_H_
#define ENV_H_
#include "types.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include <fmt/format.h>


class Env {
 public:
	 using jispFunc = std::function<std::unique_ptr<BaseValue>(std::unique_ptr<Env>, std::unique_ptr<BaseValue>)>;
  void add_builtin();  // add builtins by using lambdas???
  std::unordered_map<std::string, std::unique_ptr<jispFunc>> envs;
};
#endif
