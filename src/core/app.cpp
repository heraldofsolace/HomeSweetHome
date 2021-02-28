//
// Created by aniket on 15/02/2021.
//
#include "app.h"
namespace home_sweet_home {

std::string& prefix::must_trim_prefix(std::string &s, const std::string_view &prefix) {
  if(!has_prefix(s, prefix)) {
    std::cerr << fmt::format("{} not prefixed by {}", s, prefix);
  }

  return s.erase(0, prefix.length());
}
bool prefix::has_prefix(std::string &s, const std::string_view &prefix) {
  return s.find(prefix) == 0;
}
std::string& suffix::must_trim_suffix(std::string &s, const std::string_view &suffix) {
  if(!has_suffix(s, suffix)) {
    std::cerr << fmt::format("{} not suffixed by {}", s, suffix);
  }

  return s.erase(s.size() - suffix.length());
}
bool suffix::has_suffix(std::string &s, const std::string_view &suffix) {
  return s.rfind(suffix) == 0;
}
}