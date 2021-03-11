//
// Created by aniket on 11/03/2021.
//

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_data.h"
#include "core/template_data.h"

namespace home_sweet_home::cmd {
void setup_cmd_data(CLI::App &app, Config const &config) {

  auto sub = app.add_subcommand("data");

  sub->final_callback([&config]() { run_cmd_data(config); });
}

void run_cmd_data(Config const &config) {
  template_data data(config);
  std::cout << data.get_data().dump(2) << std::endl;
}
}