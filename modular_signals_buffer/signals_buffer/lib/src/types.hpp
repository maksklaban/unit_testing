#pragma once

#include <string>

struct Signal {
  std::string type;
  std::string value;
  int64_t time;
};