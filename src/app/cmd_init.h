//
// Created by aniket on 13/02/2021.
//

#ifndef HOMESWEETHOME_CMD_CMD_INIT_H
#define HOMESWEETHOME_CMD_CMD_INIT_H

#include <string>
#include <cstdlib>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include "CLI/CLI.hpp"
#include <git2.h>
#include "core/config.h"

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdInitOptions {
  bool apply;
  std::string repo;
};
void setup_cmd_init(CLI::App &app, Config const &config);
void run_cmd_init(CmdInitOptions const &opt,Config const  &config);

int fetch_progress(
    const git_transfer_progress *stats,
    void *payload);
}

#endif //HOMESWEETHOME_CMD_CMD_INIT_H
