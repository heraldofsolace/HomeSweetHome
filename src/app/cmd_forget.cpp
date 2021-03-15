//
// Created by aniket on 14/03/2021.
//

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_forget.h"
#include "core/shell_command.h"

namespace home_sweet_home::cmd {

using home_sweet_home::config::Config;

void setup_cmd_forget(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdForgetOptions>();
  auto sub = app.add_subcommand("forget");

  sub->add_flag("-f,--force", opt->force, "Apply the changes after initialization");
  sub->add_flag("-r,--remove", opt->remove, "Apply the changes after initialization");

  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub->final_callback([opt, &config]() { run_cmd_forget(*opt, config); });
}
void run_cmd_forget(CmdForgetOptions const &opt, Config const &config) {
  source_state s(config.destination, config.source);
  s.populate();
  std::shared_ptr<modifier> mod;
  template_data data(config);
  template_engine te(data.get_data());
  s.put_templates(te);
  if (config.dry_run) {
    mod = std::make_shared<dry_run_modifier>();
  } else {
    mod = std::make_shared<filesystem_modifier>(te);
  }
  for (auto &t: opt.targets) {
    if (opt.force) {
      if (!s.remove_entry(t, opt.remove, mod)) {
        fmt::print("{} not added", t);
      }
      continue;
    }
    int answer;
    fmt::print("Are you sure you really want to forget {}? (Y/N): ", t);
    answer = getchar();
    if (answer=='Y' || answer=='y') {
      if (!s.remove_entry(t, opt.remove, mod)) {
        fmt::print("{} not added", t);
      }
    } else {
      fmt::print("Skipping {}", t);
    }
  }

}

}