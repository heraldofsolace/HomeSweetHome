#include <iostream>
#include <fstream>
#include "CLI/CLI.hpp"
#include "cmd_init.h"
#include "cmd_add.h"
#include "cmd_dump.h"
#include "cmd_edit.h"
#include "cmd_diff.h"
#include "rang.hpp"
#include "core/config.h"
#include <git2.h>
#include <fmt/core.h>
#include <core/source_state.h>

using home_sweet_home::config::Config;
using home_sweet_home::cmd::setup_cmd_init;
using home_sweet_home::cmd::setup_cmd_add;
using home_sweet_home::cmd::setup_cmd_dump;
using home_sweet_home::cmd::setup_cmd_edit;
using home_sweet_home::cmd::setup_cmd_diff;
using CLI::App;

int main(int argc, char** argv) {
  App app{"HomeSweetHome"};
  Config config;
  git_libgit2_init();

  app.add_option("-d,--dest", config.destination, "Destination directory", true)
      ->transform([](std::string source) { return std::filesystem::absolute(source).string(); });
  app.add_option("-s,--source", config.source, "Source directory", true)
      ->transform([](std::string source) { return std::filesystem::absolute(source).string(); });
  app.add_flag("-v,--verbose", config.verbose, "Verbose");
  app.add_flag("--dry-run", config.dry_run);

  app.set_config("-c,--config", config.config_file);
  setup_cmd_init(app, config);
  setup_cmd_add(app, config);
  setup_cmd_dump(app, config);
  setup_cmd_edit(app, config);
  setup_cmd_diff(app, config);
  std::atexit([]() { std::cout << rang::style::reset; });
  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    std::cout << (e.get_exit_code()==0 ? rang::fg::blue : rang::fg::red);
    return app.exit(e);
  }

  app.callback([&app, &config]() {
    if(!app.got_subcommand("init")) {
      if(!std::filesystem::exists(config.source) || !std::filesystem::is_directory(config.source)) {
        fmt::print("Source directory {} does not exist. Please run init first", config.source);
        exit(1);
      }
      if(!std::filesystem::exists(config.destination)|| !std::filesystem::is_directory(config.destination)) {
        fmt::print("Destination directory {} does not exist. Please run init first", config.destination);
        exit(1);
      }
    }

  });

  if(app.got_subcommand("init")) {
    std::ofstream config_file;
    config_file.open(config.config_file);
    config_file << app.config_to_str(false, true);
    config_file.close();
    std::cout  << std::endl;
    std::cout << config.source << std::endl;
  }




  git_libgit2_shutdown();
  return 0;
}
