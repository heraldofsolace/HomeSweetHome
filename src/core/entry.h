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
using json = nlohmann::json;

namespace entries {
  struct entry {
    std::string target_name;
    std::string source_name;
    std::filesystem::perms perm;

    std::vector<std::shared_ptr<entry>> entries;
    std::weak_ptr<entry> parent_entry;

    virtual json to_json() {
      std::vector<json> entries_json;
      for(auto &e: entries) {
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

  struct dir_entry: public entry {
    bool is_exact;
    bool is_private;
    json to_json() override;
    YAML::Node to_yaml() override;
    dir_entry(std::string target_name, std::string source_name, const std::shared_ptr<entry>& parent_entry, bool is_private, bool is_exact):
      entry(std::move(target_name), std::move(source_name), parent_entry) {
      this->is_private = is_private;
      this->is_exact = is_exact;
    }
    void print() override {
      std::cout << "DIRECTORY" << std::endl;
      std::cout << "SOURCE: " << source_name << std::endl;
      std::cout << "TARGET: " << target_name << std::endl;
      for(auto &t: entries) {
        t->print();
      }
    }
  };

  struct file_entry: public entry {
    bool is_empty;
    bool is_encrypted;
    bool is_executable;
    bool is_once;
    int order;
    bool is_private;
    bool is_template;

    json to_json() override;
    YAML::Node to_yaml() override;
    file_entry(std::string target_name, std::string source_name, const std::shared_ptr<entry>& parent_entry, bool is_private, bool is_exact):
        entry(std::move(target_name), std::move(source_name), parent_entry) {
      this->is_private = is_private;

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
