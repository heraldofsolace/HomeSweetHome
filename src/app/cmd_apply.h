//
// Created by aniket on 10/03/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_APPLY_H
#define HOMESWEETHOME_SRC_APP_CMD_APPLY_H

#include "core/config.h"
#include "core/source_state.h"
#include <vector>

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdApplyOptions {
  std::vector<std::string> targets;
  //TODO Add rest
};
void setup_cmd_apply(CLI::App &app, Config const &config);
void run_cmd_apply(CmdApplyOptions const &opt, Config const &config);

}

#endif //HOMESWEETHOME_SRC_APP_CMD_APPLY_H
