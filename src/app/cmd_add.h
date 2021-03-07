//
// Created by aniket on 16/02/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_ADD_H
#define HOMESWEETHOME_SRC_APP_CMD_ADD_H

#include "core/config.h"
#include "core/source_state.h"
#include <vector>

namespace home_sweet_home::cmd {
  using home_sweet_home::config::Config;
struct CmdAddOptions {
  bool empty;
  bool follow;
  bool exact;
  bool recursive;
  std::vector<std::string> targets;
  //TODO Add rest
};
void setup_cmd_add(CLI::App &app, Config const &config);
void run_cmd_add(CmdAddOptions const &opt,Config const &config);

}


#endif //HOMESWEETHOME_SRC_APP_CMD_ADD_H
