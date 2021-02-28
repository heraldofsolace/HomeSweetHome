//
// Created by aniket on 14/02/2021.
//

#ifndef HOMESWEETHOME_UTILS_UTILITIES_H
#define HOMESWEETHOME_UTILS_UTILITIES_H
#include <regex>
#include <utility>

struct repo_format_guess {
  std::string rx;
  std::string format;

};

extern const repo_format_guess repo_format_guesses[8];

std::string get_git_url(const std::string& name);
#endif //HOMESWEETHOME_UTILS_UTILITIES_H
