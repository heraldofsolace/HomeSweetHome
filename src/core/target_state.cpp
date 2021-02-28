//
// Created by aniket on 20/02/2021.
//

#include "target_state.h"
#include <filesystem>
#include <fmt/core.h>
#include <iostream>
#include <numeric>
std::string target_state::add(const std::string& target) {
  auto target_name = std::filesystem::relative(target, this->target_dir);
  auto parent = target_name.parent_path();

  if(parent.string().empty()) {
    return add_file_to_entries(this->entries, target, "");
  }
  std::string pn;
  std::shared_ptr<entry> p;
  for(auto& it: parent) {
    p = find_entry(it.string());
    if(!p) {
      add(std::filesystem::path(target_dir) / pn / it);
    }
    p = find_entry(it.string());
    pn += p->source_name;
  }


  auto parent_entry = std::dynamic_pointer_cast<dir_entry>(p);
  std::cout << "PARENT" << pn << std::endl;
  return add_file_to_entries(parent_entry->entries, target, pn);




}

void target_state::p() {
  std::cout << "Printing ENTRIES" << std::endl;
  for(auto &i: entries) {
    std::cout << i.first << " >>>> " << i.second->source_name << std::endl;
  }
}
std::shared_ptr<entry> target_state::find_entry(const std::string& name) const {
  auto p = std::filesystem::path(name);
  auto _entries = this->entries;

  for(const auto & it : p.parent_path()) {
    if(_entries.find(it.string()) == _entries.end()) return nullptr;
    auto k = _entries[it.string()];
    auto d = std::dynamic_pointer_cast<dir_entry>(k);
    if(d) {
      _entries = d->entries;

    } else {
      fmt::print("{} not a directory", it.string());
      exit(1);
    }
  }
  if(_entries.find(p.filename()) != _entries.end()) {
    return _entries[p.filename()];
  }
  return nullptr;
}
std::string target_state::add_file_to_entries(std::unordered_map<std::string, std::shared_ptr<entry>> &_entries, const std::string& target, const std::string& parent_source_name) const {

  auto target_name = std::filesystem::relative(target, this->target_dir);
  auto name = target_name.filename();

  if(std::filesystem::is_regular_file(target)) {
    if(!find_entry(name)) {
      bool is_private = (std::filesystem::status(target).permissions() & std::filesystem::perms::group_all & std::filesystem::perms::others_all) == std::filesystem::perms::none;
      auto sname = file_entry::make_sourcename(name.string(), parent_source_name, is_private);
      file_entry d;
      d.source_name = sname;
      d.target_name = name;
      d.is_private = is_private;

      auto f = std::make_shared<file_entry>(d);
      _entries[name] = f;
      std::filesystem::copy(target, std::filesystem::path(source_dir) / f->source_name, std::filesystem::copy_options::update_existing);

      return  f->source_name;
    }
  }

  if(std::filesystem::is_directory(target)) {

    if(!find_entry(name)) {
      bool is_private = (std::filesystem::status(target).permissions() & std::filesystem::perms::group_all & std::filesystem::perms::others_all) == std::filesystem::perms::none;
      auto sname = dir_entry::make_sourcename(name.string(), parent_source_name, is_private);
      dir_entry d;
      d.source_name = sname;
      d.target_name = name;
      d.is_private = is_private;
      d.is_exact = false;
      auto f = std::make_shared<dir_entry>(d);
      _entries[name] = f;
      std::filesystem::create_directory(std::filesystem::path(source_dir)  / f->source_name);

      return f->source_name;
    }
  }

  return "";
}
void target_state::populate(std::unordered_map<std::string, std::shared_ptr<entry>>& _entries, const std::string& source) {
  for(const auto& file: std::filesystem::directory_iterator(source)) {
    auto rel_path = std::filesystem::relative(file, source);
    const auto file_name = file.path().filename().string();
    if(file.is_directory()) {
      auto vec = dir_entry::make_dir_targetnames(rel_path.string());
      std::string source;
      dir_entry d;
      for(auto &t: vec) {
        source += t.first;
      }
      d.source_name = source;
      d.target_name = file_name;
      d.is_private = vec[vec.size() - 1].second;
      auto dir = std::make_shared<dir_entry>(d);
      _entries[dir->target_name] = dir;
    } else if(file.is_regular_file()) {
      auto f = std::make_shared<file_entry>(file_name);
      _entries[f->target_name] = f;
    }
  }
}
void target_state::populate_file_to_entries(std::unordered_map<std::string, std::shared_ptr<entry>> &_entries,
                                            const std::string &target) const {

}
void target_state::populate(const std::string& source) {
  populate(entries, source);
}
void target_state::populate() {
  populate(source_dir);
}


