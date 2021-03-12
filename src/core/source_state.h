//
// Created by aniket on 20/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H
#define HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H

#include <string>
#include <utility>
#include <filesystem>
#include <memory>
#include <variant>
#include "entry.h"
#include "core/modifier.h"

using entries::entry;
using entries::dir_entry;
using entries::file_entry;
namespace fs = std::filesystem;

struct source_state {
  fs::path target_dir;
  fs::path source_dir;
  std::shared_ptr<entry> source_dir_entry;

  static std::shared_ptr<entry> find_by_target_name(const std::shared_ptr<entry> &ent, const std::string &t_name);
  static std::shared_ptr<entry> find_by_source_name(const std::shared_ptr<entry> &ent, const std::string &t_name);
  void add(const std::string &target, std::shared_ptr<entry> current, bool force, std::shared_ptr<modifier> mod);
  void add_path(const std::string &target, std::shared_ptr<entry> current, bool force, std::shared_ptr<modifier> mod);
  void print();

  std::pair<std::string,
            std::variant<file_entry::file_entry_info,
                         dir_entry::dir_entry_info>> make_target_name_from_source_name(std::string source_name,
                                                                                       bool is_dir);
  static std::string make_source_name_from_target_name(const std::string &target_name);
  std::string get_target_name(const std::string &source_name);
  [[nodiscard]] std::shared_ptr<entry> locate_entry(std::string target_name) const;
  void populate(const std::string &source, std::shared_ptr<entry> current);
  void populate();
  void apply(const std::shared_ptr<modifier> &mod, const std::shared_ptr<entry> &e) const;
  void apply(const std::shared_ptr<modifier> &mod, const std::string &target_name = "", bool recursive = true);
  json dump_json();
  YAML::Node dump_yaml();
  source_state() {
    source_dir_entry = std::make_shared<entry>("", "", nullptr);
  }

  source_state(std::string target_dir, std::string source_dir) : source_state() {
    this->source_dir = std::move(source_dir);
    this->target_dir = std::move(target_dir);
  }
};

#endif //HOMESWEETHOME_SRC_CORE_SOURCE_STATE_H
