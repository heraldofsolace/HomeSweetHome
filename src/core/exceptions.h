//
// Created by aniket on 28/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_EXCEPTIONS_H
#define HOMESWEETHOME_SRC_CORE_EXCEPTIONS_H

#include <exception>

class suffix_not_present_esception: public std::exception {
  virtual const char* what() const noexcept {
    return "String not suffixed";
  }
};

#endif //HOMESWEETHOME_SRC_CORE_EXCEPTIONS_H
