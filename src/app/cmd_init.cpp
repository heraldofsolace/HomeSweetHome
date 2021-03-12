//
// Created by aniket on 13/02/2021.
//

#include "cmd_init.h"
#include "core/config.h"
#include "CLI/CLI.hpp"
#include "core/modifier.h"
#include "core/utilities.h"
#include <git2.h>
#include <filesystem>
#include <rang.hpp>
#include <fmt/core.h>

namespace home_sweet_home::cmd {
int fetch_progress(
    const git_transfer_progress *stats,
    void *payload)
{
  int fetch_percent =
      (100 * stats->received_objects) /
          stats->total_objects;
  int index_percent =
      (100*stats->indexed_objects)/
          stats->total_objects;
  int kbytes = stats->received_bytes/1024;

  std::cout << "\rFetched " << fetch_percent << "%\t" << "(" << kbytes << "KB,\t" << stats->received_objects << "/"
            << stats->total_objects << ")";
  std::cout.flush();

  return 0;
}

void setup_cmd_init(CLI::App &app, Config const &config) {
  auto opt = std::make_shared<CmdInitOptions>();
  auto sub = app.add_subcommand("init");

  sub->add_flag("--apply", opt->apply, "Apply the changes after initialization");
  sub->add_option("repo", opt->repo, "URL of the git repository");

  sub->final_callback([opt, &config]() { run_cmd_init(*opt, config); });
}

void run_cmd_init(CmdInitOptions const &opt, Config const &config) {
  std::unique_ptr<modifier> mod;
  template_data data(config);
  template_engine te(data.get_data());
  if (config.dry_run) {
    mod = std::make_unique<dry_run_modifier>();
  } else {
    mod = std::make_unique<filesystem_modifier>(te);
  }
  mod->create_directories(config.config_dir);
  if (opt.repo.empty()) {
    mod->create_directories(config.source);
    mod->create_directories(config.destination);
  } else {

    mod->create_directories(config.destination);
    fmt::print("Fetching: {}", get_git_url(opt.repo));

    if (!config.dry_run) {

      git_repository *repo = nullptr;
      git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
      opts.fetch_opts.callbacks.transfer_progress = fetch_progress;
      int status = git_clone(&repo, get_git_url(opt.repo).c_str(), config.source.c_str(), &opts);
      std::cout << std::endl;
      if (status!=0) {
        std::cerr << git_error_last()->message << std::endl;
      }
      git_repository_free(repo);

    }

  }



}
}
