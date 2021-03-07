//
// Created by aniket on 07/03/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_DUMP_H
#define HOMESWEETHOME_SRC_APP_CMD_DUMP_H

#include "core/config.h"
#include "core/source_state.h"
#include <vector>

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdDumpOptions {
  std::string format = "json";
  std::vector<std::string> targets;
  //TODO Add rest
};
void setup_cmd_dump(CLI::App &app, Config const &config);
void run_cmd_dump(CmdDumpOptions const &opt, Config const &config);

}

#endif //HOMESWEETHOME_SRC_APP_CMD_DUMP_H
