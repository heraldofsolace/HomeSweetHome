//
// Created by aniket on 11/03/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_TEMPLATE_DATA_H
#define HOMESWEETHOME_SRC_CORE_TEMPLATE_DATA_H

#include <nlohmann/json.hpp>
#include "config.h"
using json = nlohmann::json;
using config = home_sweet_home::config::Config;
class template_data {
  json data;

  json get_kernel_info();
  json get_os_info();

public:
  json get_data();
  explicit template_data(const config &conf);
};

#endif //HOMESWEETHOME_SRC_CORE_TEMPLATE_DATA_H
