//
// Created by aniket on 20/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H
#define HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H

#include <string>
#include <utility>
#include <filesystem>
#include "entry.h"

using entries::entry;
using entries::dir_entry;
using entries::file_entry;
namespace fs = std::filesystem;

struct source_state {
  fs::path target_dir;
  fs::path source_dir;
  std::shared_ptr<entry> source_dir_entry;

  std::shared_ptr<entry> find_by_target_name(std::shared_ptr<entry> ent, std::string t_name);
  std::shared_ptr<entry> find_by_source_name(std::shared_ptr<entry> ent, std::string t_name);
  void add(const std::string& target, std::shared_ptr<entry> current);
  void add_path(const std::string& target, std::shared_ptr<entry> current);
  void print();

  std::string make_target_name_from_source_name(std::string source_name);
  std::string make_source_name_from_target_name(const std::string& target_name);
  std::string get_target_name(const std::string& source_name);

  void populate(const std::string& source, std::shared_ptr<entry> current);
  void populate();

  json dump_json();
  YAML::Node dump_yaml();
  source_state() {
    source_dir_entry = std::make_shared<entry>("","", nullptr);
  }

  source_state(std::string target_dir, std::string source_dir): source_state() {
    this->source_dir = std::move(source_dir);
    this->target_dir = std::move(target_dir);
  }
};

#endif //HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H
