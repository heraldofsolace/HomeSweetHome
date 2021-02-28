//
// Created by aniket on 14/02/2021.
//

#include "utilities.h"
#include <regex>
#include <iostream>
#include <fmt/core.h>
#include <rang.hpp>
#include "app.h"
#include <filesystem>
const repo_format_guess repo_format_guesses[8] = {
    { .rx =  "^[-0-9A-Za-z]+$", .format =  "https://github.com/{}/dotfiles.git" },
    { .rx =  R"(^[-0-9A-Za-z]+/[-0-9A-Za-z]+\.git$)", .format =  "https://github.com/{}" },
    { .rx =  "^[-0-9A-Za-z]+/[-0-9A-Za-z]+$", .format =  "https://github.com/{}.git" },
    { .rx =  "^[-.0-9A-Za-z]+/[-0-9A-Za-z]+$", .format =  "https://{}/dotfiles.git" },
    { .rx =  "^[-.0-9A-Za-z]+/[-0-9A-Za-z]+/[-0-9A-Za-z]+$", .format =  "https://{}.git" },
    { .rx =  R"(^[-.0-9A-Za-z]+/[-0-9A-Za-z]+/[-0-9A-Za-z]+\.git$)", .format =  "https://{}" },
    { .rx =  R"(^sr\.ht/~[-0-9A-Za-z]+$)", .format =  "https://git.{}/dotfiles" },
    { .rx =  R"(^sr\.ht/~[-0-9A-Za-z]+/[-0-9A-Za-z]+$)", .format =  "https://git.{}" },

};

std::string get_git_url(const std::string& name) {
  for(const auto& guess: repo_format_guesses) {
    auto reg = std::regex(guess.rx , std::regex::ECMAScript);
    if(std::regex_match(name, reg)) { return fmt::format(guess.format, name); }
  }

  return name;
}
