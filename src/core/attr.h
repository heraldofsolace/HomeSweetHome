//
// Created by aniket on 15/02/2021.
//

#ifndef HOMESWEETHOME_SRC_INTERNAL_ATTR_H
#define HOMESWEETHOME_SRC_INTERNAL_ATTR_H

#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>
enum source_filetype {
  SOURCE_FILE_TYPE_CREATE,
  SOURCE_FILE_TARGET_TYPE,
  SOURCE_FILE_TYPE_FILE,
  SOURCE_FILE_TYPE_MODIFY,
  SOURCE_FILE_TYPE_SCRIPT,
  SOURCE_FILE_TYPE_SYMLINK
};

struct entry {
  std::string target_name;
  std::string source_name;

  virtual void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name);
  std::filesystem::perms perm;
};

struct dir_attr: public entry {
  bool is_exact;
  bool is_private;

  std::unordered_map<std::string, std::shared_ptr<entry>> entries;
  dir_attr(std::string target_name, bool is_private);
  explicit dir_attr(const std::string& source_name);
  void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) override;
};

struct file_attr: public entry {
  source_filetype type;
  bool is_empty;
  bool is_encrypted;
  bool is_executable;
  bool is_once;
  int order;
  bool is_private;
  bool is_template;

  file_attr(std::string target_name, bool is_private);
  explicit file_attr(const std::string& source_name);
  void get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) override;



};

#endif //HOMESWEETHOME_SRC_INTERNAL_ATTR_H
