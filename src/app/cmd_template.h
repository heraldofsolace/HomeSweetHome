//
// Created by aniket on 12/03/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_TEMPLATE_H
#define HOMESWEETHOME_SRC_APP_CMD_TEMPLATE_H

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdTemplateOptions {
  std::string format = "diff";
  std::vector <std::string> targets;
  //TODO Add rest
};
void setup_cmd_diff(CLI::App &app, Config const &config);
void run_cmd_diff(CmdDiffOptions const &opt, Config const &config);

}

#endif //HOMESWEETHOME_SRC_APP_CMD_TEMPLATE_H
