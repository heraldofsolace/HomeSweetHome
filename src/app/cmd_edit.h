//
// Created by aniket on 09/03/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_EDIT_H
#define HOMESWEETHOME_SRC_APP_CMD_EDIT_H

#include "core/config.h"
#include "core/source_state.h"
#include <vector>

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdEditOptions {
  bool prompt;
  bool apply;
  bool diff;
  std::vector<std::string> targets;
  //TODO Add rest
};
void setup_cmd_edit(CLI::App &app, Config const &config);
void run_cmd_edit(CmdEditOptions const &opt,Config const &config);

}

#endif //HOMESWEETHOME_SRC_APP_CMD_EDIT_H
