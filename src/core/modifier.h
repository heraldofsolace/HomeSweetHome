//
// Created by aniket on 10/03/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_MODIFIER_H
#define HOMESWEETHOME_SRC_CORE_MODIFIER_H

#include <string>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;
struct modifier {
  virtual void create_directories(fs::path path) = 0;
  virtual void create_directory(fs::path path, fs::path attributes) = 0;
  virtual void create_file(fs::path path, std::string text) = 0;
  virtual void copy_file(fs::path from, fs::path to, fs::copy_options options) = 0;
  virtual void delete_file(fs::path path) = 0;

};

struct filesystem_modifier : public modifier {
  void create_directory(fs::path path, fs::path attributes) override;
  void create_directories(fs::path path) override;
  void create_file(fs::path path, std::string text) override;
  void copy_file(fs::path from, fs::path to, fs::copy_options options) override;
  void delete_file(fs::path path) override;
};

struct dry_run_modifier : public modifier {
  void create_directory(fs::path path, fs::path attributes) override;
  void create_directories(fs::path path) override;
  void create_file(fs::path path, std::string text) override;
  void copy_file(fs::path from, fs::path to, fs::copy_options options) override;
  void delete_file(fs::path path) override;
};

struct logging_modifier : public modifier {
  std::unique_ptr<modifier> actual_modifier;
  fs::path log_path;

  void create_directory(fs::path path, fs::path attributes) override;
  void create_directories(fs::path path) override;
  void create_file(fs::path path, std::string text) override;
  void copy_file(fs::path from, fs::path to, fs::copy_options options) override;
  void delete_file(fs::path path) override;

  logging_modifier(std::unique_ptr<modifier> actual_modifier) : actual_modifier(std::move(actual_modifier)) {}
};

#endif //HOMESWEETHOME_SRC_CORE_MODIFIER_H
