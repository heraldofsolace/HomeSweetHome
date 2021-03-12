//
// Created by aniket on 09/03/2021.
//
#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include "cmd_diff.h"
#include "core/diff_match_patch.h"
#include "core/shell_command.h"
#include "core/path_formatter.h"

namespace home_sweet_home::cmd {
void setup_cmd_diff(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdDiffOptions>();
  auto sub = app.add_subcommand("diff");

  sub->add_option("-f,--format", opt->format, "Apply the changes after initialization");
  sub->add_option("targets", opt->targets)
      ->transform([](const std::string &s) { return std::filesystem::absolute(s); });

  sub -> final_callback([opt, &config]() { run_cmd_diff(*opt, config); });
}

void run_cmd_diff(CmdDiffOptions const &opt,Config const &config) {
  source_state s(config.destination, config.source);
  s.populate();
  template_data data(config);
  template_engine te(data.get_data());
  s.put_templates(te);
  if(opt.targets.empty()) {
    s.walk([&s, &te](const std::shared_ptr<entry>& e) {

      if(e->source_name.empty() || e->target_name.empty()) return;
      auto f = std::dynamic_pointer_cast<file_entry>(e);

      if(f) {
        fmt::print("diff {} with {}\n", s.source_dir / e->source_name, s.target_dir / e->target_name);
        if(f->info.is_template) {
          std::ifstream ifs(s.source_dir / e->source_name);
          auto result = te.render(ifs);
          shell_command sh(fmt::format("diff - {}", (s.target_dir / f->target_name)));
          sh.std_in = result;
          sh.execute();

          std::cout << (sh.exit_status != 0 ? sh.std_out : "No change") << std::endl;
        } else {
          shell_command sh(fmt::format("diff {} {}", (s.source_dir / f->source_name), (s.target_dir / f->target_name)));
          sh.execute();
          std::cout << (sh.exit_status != 0 ? sh.std_out : "No change") << std::endl;
        }
      }

    });
  }
  for(auto &target: opt.targets) {
    auto entry = s.locate_entry(target);
    auto f = std::dynamic_pointer_cast<file_entry>(entry);
    if(f) {

      if(f->info.is_template) {
        std::ifstream ifs(s.source_dir / entry->source_name);
        auto result = te.render(ifs);
        shell_command sh(fmt::format("diff - {}", (s.target_dir / f->target_name)));
        sh.std_in = result;
        sh.execute();
        std::cout << (sh.exit_status != 0 ? sh.std_out : "No change") << std::endl;
      } else {
        shell_command sh(fmt::format("diff {} {}", (s.source_dir / f->source_name), (s.target_dir / f->target_name)));
        sh.execute();
        std::cout << (sh.exit_status != 0 ? sh.std_out : "No change") << std::endl;
      }
    }

  }

}
}
