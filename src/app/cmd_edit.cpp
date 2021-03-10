//
// Created by aniket on 09/03/2021.
//
#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_edit.h"
#include "core/shell_command.h"

namespace home_sweet_home::cmd {

using home_sweet_home::config::Config;

void setup_cmd_edit(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdEditOptions>();
  auto sub = app.add_subcommand("edit");

  sub->add_flag("-p,--prompt", opt->prompt, "Apply the changes after initialization");
  sub->add_flag("-a,--apply", opt->apply, "Apply the changes after initialization");
  sub->add_flag("-d,--diff", opt->diff, "Apply the changes after initialization");

  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub -> final_callback([opt, &config]() { run_cmd_edit(*opt, config); });
}
void run_cmd_edit(CmdEditOptions const &opt,Config const &config) {
  auto editor = std::getenv("EDITOR");
  if(!editor) {
    std::cerr << "$EDITOR not set" << std::endl;
    exit(1);
  }
  source_state s(config.destination, config.source);
  s.populate();
  for(auto &target: opt.targets) {
    auto entry = s.locate_entry(target);
    auto command = fmt::format("{} {}", editor, (s.source_dir / entry->source_name).string());
    system(command.c_str());
  }

}

}