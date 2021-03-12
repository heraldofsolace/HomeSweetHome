//
// Created by aniket on 12/03/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_TEMPLATE_ENGINE_H
#define HOMESWEETHOME_SRC_CORE_TEMPLATE_ENGINE_H

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include "template_data.h"
using inja::Environment;
using nlohmann::json;

class template_engine {
  Environment env;
  json data;

public:
  std::string render(std::ifstream &fs);
  std::string render(std::string template_text);
  template_engine(json data) : data(data) {
    //TODO Add functions
  }
};

#endif //HOMESWEETHOME_SRC_CORE_TEMPLATE_ENGINE_H
