//
// Created by aniket on 27/02/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_ENTRY_H
#define HOMESWEETHOME_SRC_CORE_ENTRY_H
#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <range/v3/all.hpp>
#include "modifier.h"

using json = nlohmann::json;

namespace entries {
struct entry {
  std::string target_name;
  std::string source_name;
  std::filesystem::perms perm;

  std::vector<std::shared_ptr<entry>> entries;
  std::weak_ptr<entry> parent_entry;

  virtual void apply(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
    ranges::for_each(entries, [&source_dir, &target_dir, mod](auto e) { e->apply(source_dir, target_dir, mod); });
  }
  virtual void apply_backwards(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
    if (auto pe = parent_entry.lock()) {
      pe->apply_backwards(source_dir, target_dir, mod);
    }
  }
  virtual json to_json() {
    std::vector<json> entries_json;
    for (auto &e: entries) {
      entries_json.push_back(e->to_json());
    }

    return entries_json;
  }
  virtual YAML::Node to_yaml() {
      YAML::Emitter out;
      out << YAML::BeginSeq;
      for(auto &t: entries) {
        out << t->to_yaml();
      }
      out << YAML::EndSeq;
      YAML::Node node = YAML::Load(out.c_str());

      return node;
    }
    entry(std::string target_name, std::string source_name, const std::shared_ptr<entry>& parent_entry):
        target_name(std::move(target_name)), source_name(std::move(source_name)), parent_entry(parent_entry) {}

    virtual void print() {
      std::cout << "SOURCE: " << source_name << std::endl;
      std::cout << "TARGET: " << target_name << std::endl;
      for(auto &t: entries) {
        t->print();
      }
    }

  };

struct dir_entry : public entry {
  struct dir_entry_info {
    bool is_exact = false;
    bool is_private = false;
  };

  dir_entry_info info{};

  json to_json() override;
  YAML::Node to_yaml() override;
  void apply(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) override;
  void apply_backwards(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) override;
  dir_entry(std::string target_name,
            std::string source_name,
            const std::shared_ptr<entry> &parent_entry,
            bool is_private,
            bool is_exact) :
      entry(std::move(target_name), std::move(source_name), parent_entry) {
    this->info = {.is_exact = is_exact, .is_private = is_private};
  }
  void print() override {
    std::cout << "DIRECTORY" << std::endl;
    std::cout << "SOURCE: " << source_name << std::endl;
    std::cout << "TARGET: " << target_name << std::endl;
    for (auto &t: entries) {
        t->print();
      }
    }
  };

struct file_entry : public entry {
  struct file_entry_info {
    bool is_empty = false;
    bool is_encrypted = false;
    bool is_executable = false;
    bool is_once = false;
    int order = 1;
    bool is_private = false;
    bool is_template = false;
  };

  file_entry_info info;

  void apply(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) override;
  void apply_backwards(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) override;
  json to_json() override;
  YAML::Node to_yaml() override;
  file_entry(std::string target_name,
             std::string source_name,
             const std::shared_ptr<entry> &parent_entry,
             bool is_private,
             bool is_template) :
      entry(std::move(target_name), std::move(source_name), parent_entry) {
    this->info = {.is_private = is_private, .is_template = is_template};

  }

  void print() override {
    std::cout << "FILE" << std::endl;
      std::cout << "SOURCE: " << source_name << std::endl;
      std::cout << "TARGET: " << target_name << std::endl;
      for(auto &t: entries) {
        t->print();
      }
    }
  };
}


#endif //HOMESWEETHOME_SRC_CORE_ENTRY_H
