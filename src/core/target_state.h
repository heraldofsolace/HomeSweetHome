//
// Created by aniket on 20/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_TARGET_STATE_H
#define HOMESWEETHOME_SRC_CORE_TARGET_STATE_H

#include <string>
#include <unordered_map>
#include "entry.h"
struct target_state {
  std::string target_dir;
  std::string source_dir;
  std::unordered_map<std::string, std::shared_ptr<entry>> entries;

  std::string add(const std::string& target);
  std::shared_ptr<entry> find_entry(const std::string& name) const;
  void p();
  std::string add_file_to_entries(std::unordered_map<std::string, std::shared_ptr<entry>>& _entries, const std::string& target, const std::string& parent_source_name) const;
  void populate_file_to_entries(std::unordered_map<std::string, std::shared_ptr<entry>>& _entries, const std::string& source) const;
  void populate(std::unordered_map<std::string, std::shared_ptr<entry>>& _entries, const std::string& source);
  void populate(const std::string& source);
  void populate();
};

#endif //HOMESWEETHOME_SRC_CORE_TARGET_STATE_H
