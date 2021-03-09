//
// Created by aniket on 16/02/2021.
//

#include <CLI/CLI.hpp>
#include <filesystem>
#include "cmd_add.h"
#include "core/config.h"
#include <fmt/core.h>
#include <core/source_state.h>

namespace home_sweet_home::cmd {
  void setup_cmd_add(CLI::App &app, Config const &config) {
    auto opt = std::make_shared<CmdAddOptions>();
    auto sub = app.add_subcommand("add");

    sub->add_flag("-e,--empty", opt->empty, "Apply the changes after initialization");
    sub->add_flag("-s,--follow-symlink", opt->follow, "Apply the changes after initialization");
    sub->add_flag("-x,--exact", opt->exact, "Apply the changes after initialization");
    sub->add_flag("-r,--recursive", opt->recursive, "Apply the changes after initialization");
    sub->add_flag("-f,--force", opt->force, "Apply the changes after initialization");
    sub->add_option("targets", opt->targets)
        ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

    sub -> final_callback([opt, &config]() { run_cmd_add(*opt, config); });
  }

  void run_cmd_add(CmdAddOptions const &opt,Config const &config) {
    source_state ts(config.destination, config.source);
    ts.populate();
    for(auto &arg: opt.targets) {
      ts.add_path(arg, nullptr, opt.force);
      if(opt.recursive && std::filesystem::is_directory(arg)) {
        for(const auto& file: std::filesystem::recursive_directory_iterator(arg)) {
          ts.add_path(file.path().string(), nullptr, opt.force);
        }
      }
    }

  }
}
