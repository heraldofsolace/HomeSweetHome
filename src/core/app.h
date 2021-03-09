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
      static std::string& must_trim_prefix(std::string &s, const std::string_view &prefix);
      static bool has_prefix(std::string &s, const std::string_view &prefix);

    };

    struct suffix {
      constexpr static const std::string_view suffix_delimiter{"##"}    ;
      constexpr static const std::string_view after_suffix{"after"}    ;
      constexpr static const std::string_view  before_suffix {"before"}    ;
      constexpr static const std::string_view  create_suffix {"create"}    ;
      constexpr static const std::string_view  dot_suffix { "dot"}       ;
      constexpr static const std::string_view  empty_suffix  { "empty"}    ;
      constexpr static const std::string_view  encrypted_suffix {"encrypted"} ;
      constexpr static const std::string_view  exact_suffix  {"exact"}    ;
      constexpr static const std::string_view  executable_suffix{"executable"} ;
      constexpr static const std::string_view  modify_suffix {"modify"}    ;
      constexpr static const std::string_view   once_suffix  {"once"}     ;
      constexpr static const std::string_view  private_suffix {"private"}   ;
      constexpr static const std::string_view   run_suffix   {"run"}     ;
      constexpr static const std::string_view symlink_suffix{"symlink"};
      constexpr static const std::string_view hidden_suffix{"hidden"};
      constexpr static const std::string_view template_suffix{"tmpl"};


      static std::string& must_trim_suffix(std::string &s, const std::string_view &suffix);
      static bool has_suffix(std::string &s, const std::string_view &suffix);
      static std::vector<std::string> get_suffix_list(std::string s);
      static std::string remove_suffixes(std::string s);
    };

  }

#endif //HOMESWEETHOME_SRC_INTERNAL_APP_H
