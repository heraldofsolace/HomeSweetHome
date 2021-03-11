//
// Created by aniket on 14/02/2021.
//

#ifndef HOMESWEETHOME_CONFIG_CONFIG_H
#define HOMESWEETHOME_CONFIG_CONFIG_H

#include <string>

namespace home_sweet_home::config {
struct Config {
  std::string homedir;
  std::string xdg_data_dir;
  std::string xdg_config_dir;
  std::string username;

  std::string source;
  std::string destination;

  std::string config_dir;
  std::string config_file;

  bool verbose = false;
  bool dry_run = false;
  Config();
};
}


#endif //HOMESWEETHOME_CONFIG_CONFIG_H
