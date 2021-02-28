//
// Created by aniket on 27/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_ENTRY_H
#define HOMESWEETHOME_SRC_CORE_ENTRY_H
#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>

struct entry {
  std::string target_name;
  std::string source_name;

  virtual void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name);
  std::filesystem::perms perm;
};

struct dir_entry: public entry {
  bool is_exact;
  bool is_private;

  std::unordered_map<std::string, std::shared_ptr<entry>> entries;
  void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) override;
  static std::string make_sourcename(std::string name, std::string parent_source_name, bool _private);
  static std::tuple<std::string, bool> make_targetname(std::string name);
  static std::vector<std::tuple<std::string, bool>> make_dir_targetnames(std::string name);
};

struct file_entry: public entry {
  bool is_empty;
  bool is_encrypted;
  bool is_executable;
  bool is_once;
  int order;
  bool is_private;
  bool is_template;

  void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) override;
  static std::string make_sourcename(std::string name, std::string parent_source_name, bool _private);
  static std::tuple<std::string, bool> make_targetname(std::string name);
};

#endif //HOMESWEETHOME_SRC_CORE_ENTRY_H
