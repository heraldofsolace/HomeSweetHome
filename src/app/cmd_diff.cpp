//
// Created by aniket on 09/03/2021.
//
#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_diff.h"
#include "core/diff_match_patch.h"
#include "core/shell_command.h"
namespace home_sweet_home::cmd {
void setup_cmd_diff(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdDiffOptions>();
  auto sub = app.add_subcommand("diff");

  sub->add_flag("-f,--format", opt->format, "Apply the changes after initialization");
  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub -> final_callback([opt, &config]() { run_cmd_diff(*opt, config); });
}

void run_cmd_diff(CmdDiffOptions const &opt,Config const &config) {
  source_state s(config.destination, config.source);
  s.populate();
  for(auto &target: opt.targets) {
    auto entry = s.locate_entry(target);
    shell_command sh(fmt::format("diff {} {}", (s.source_dir / entry->source_name).string(), (s.target_dir / entry->target_name).string()));
    sh.execute();
    std::cout << sh.std_out << std::endl;
  }

}
}
