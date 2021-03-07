//
// Created by aniket on 07/03/2021.
//
#include <CLI/CLI.hpp>
#include <filesystem>
#include "cmd_dump.h"
#include "core/config.h"
#include <fmt/core.h>
#include <core/source_state.h>

namespace home_sweet_home::cmd {

  void setup_cmd_dump(CLI::App &app, Config const &config) {
    auto opt = std::make_shared<CmdDumpOptions>();
    auto sub = app.add_subcommand("dump");

    sub -> add_option("-f,--format", opt->format, "Format", true);
    sub -> add_option("targets", opt->targets)->transform([](const std::string& s) { return std::filesystem::absolute(s); });

    sub -> final_callback([opt, &config]() { run_cmd_dump(*opt, config); });
  }

  void run_cmd_dump(CmdDumpOptions const &opt, Config const &config) {
    source_state s(config.destination, config.source);
    s.populate();

    if(opt.format == "json") {
      std::cout << s.dump_json().dump(4) << std::endl;
    } else if(opt.format == "yaml") {
      std::cout << s.dump_yaml() << std::endl;
    }
  }
}