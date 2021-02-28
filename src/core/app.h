//
// Created by aniket on 15/02/2021.
//

#ifndef HOMESWEETHOME_SRC_INTERNAL_APP_H
#define HOMESWEETHOME_SRC_INTERNAL_APP_H

#include <string_view>
#include <iostream>
#include <fmt/core.h>
namespace home_sweet_home {
    struct prefix {
      constexpr static const std::string_view ignore_prefix{ "."};
      constexpr static const std::string_view after_prefix{"after_"}    ;
      constexpr static const std::string_view  before_prefix {"before_"}    ;
      constexpr static const std::string_view  create_prefix {"create_"}    ;
      constexpr static const std::string_view  dot_prefix { "dot_"}       ;
      constexpr static const std::string_view  empty_prefix  { "empty_"}    ;
      constexpr static const std::string_view  encrypted_prefix {"encrypted_"} ;
      constexpr static const std::string_view  exact_prefix  {"exact_"}    ;
      constexpr static const std::string_view  executable_prefix{"executable_"} ;
      constexpr static const std::string_view  modify_prefix {"modify_"}    ;
      constexpr static const std::string_view   once_prefix  {"once_"}     ;
      constexpr static const std::string_view  private_prefix {"private_"}   ;
      constexpr static const std::string_view   run_prefix   {"run_"}     ;
      constexpr static const std::string_view symlink_prefix { "symlink_"}   ;

      static std::string& must_trim_prefix(std::string &s, const std::string_view &prefix);
      static bool has_prefix(std::string &s, const std::string_view &prefix);
    };

    struct suffix {
      constexpr static const std::string_view template_suffix {".tmpl"};
      static std::string& must_trim_suffix(std::string &s, const std::string_view &suffix);
      static bool has_suffix(std::string &s, const std::string_view &suffix);
    };

  }

#endif //HOMESWEETHOME_SRC_INTERNAL_APP_H
