//
// Created by aniket on 10/03/2021.
//

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_apply.h"

namespace home_sweet_home::cmd {
void setup_cmd_apply(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdApplyOptions>();
  auto sub = app.add_subcommand("add");

  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub->final_callback([opt, &config]() { run_cmd_apply(*opt, config); });
}

void run_cmd_apply(CmdApplyOptions const &opt, Config const &config) {

}
}
