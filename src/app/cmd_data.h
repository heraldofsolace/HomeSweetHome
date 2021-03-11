//
// Created by aniket on 11/03/2021.
//

#ifndef HOMESWEETHOME_SRC_APP_CMD_DATA_H
#define HOMESWEETHOME_SRC_APP_CMD_DATA_H

#include "core/config.h"

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;

void setup_cmd_data(CLI::App &app, Config const &config);
void run_cmd_data(Config const &config);

}

#endif //HOMESWEETHOME_SRC_APP_CMD_DATA_H
