//
// Created by aniket on 10/03/2021.
//

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_apply.h"
#include "core/template_engine.h"
#include "core/template_data.h"
namespace home_sweet_home::cmd {
void setup_cmd_apply(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdApplyOptions>();
  auto sub = app.add_subcommand("apply");

  sub->add_flag("-r,--recursive,!--no-recursive", opt->recursive);
  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub->final_callback([opt, &config]() { run_cmd_apply(*opt, config); });
}

void run_cmd_apply(CmdApplyOptions const &opt, Config const &config) {
  source_state s(config.destination, config.source);
  s.populate();
  std::shared_ptr<modifier> mod;
  template_data data(config);
  template_engine te(data.get_data());
  if (config.dry_run) {
    mod = std::make_shared<dry_run_modifier>();
  } else {
    mod = std::make_shared<filesystem_modifier>(te);
  }
  if (opt.targets.empty()) {
    s.apply(mod);
  } else {
    ranges::for_each(opt.targets, [&opt, &s, &mod](auto target) {
      s.apply(mod, target, opt.recursive);
    });
  }
}
}
