//
// Created by aniket on 15/02/2021.
//
#include "app.h"
#include <range/v3/all.hpp>

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
    auto suffixes = get_suffix_list(s);
    return ranges::find(suffixes, suffix) != suffixes.end();
  }
  std::vector<std::string> suffix::get_suffix_list(std::string s) {
    std::vector<std::string> suffixes;
    auto i = s.find(suffix_delimiter);
    if(i == std::string::npos) {
      std::cerr << fmt::format("{} has no suffix", s);
      exit(1);
    }
    std::string all_suffixes = s.substr(i + 2);
    return all_suffixes | ranges::views::split('_') | ranges::to<std::vector<std::string>>();

  }
std::string suffix::remove_suffixes(std::string s) {
  auto i = s.find(suffix_delimiter);
  if(i == std::string::npos) {
    std::cerr << fmt::format("{} has no suffix", s);
    exit(1);
  }
  return s.substr(0, i);
}
}