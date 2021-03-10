//
// Created by aniket on 20/02/2021.
//

#include "source_state.h"
#include <filesystem>
#include <fmt/core.h>
#include <iostream>
#include <numeric>
#include <utility>
#include <fmt/core.h>
#include <range/v3/all.hpp>
#include "app.h"

std::shared_ptr<entry> source_state::find_by_target_name(const std::shared_ptr<entry>& ent, const std::string& t_name) {
  for (auto &t: ent->entries) {
    if (t->target_name==t_name)
      return t;
  }
  return nullptr;
}

std::shared_ptr<entry> source_state::find_by_source_name(const std::shared_ptr<entry>& ent, const std::string& t_name) {
  for(auto &t: ent->entries) {
    if(t->source_name == t_name) return t;
  }
  return nullptr;
}

void source_state::add(const std::string &target, std::shared_ptr<entry> current, bool force) {

  auto parent = std::filesystem::path(target).parent_path();
  auto filename = std::filesystem::path(target).filename();
  if (current==nullptr)
    current = source_dir_entry;
  std::filesystem::path parent_path;
  for (auto &t: parent) {
    auto k = find_by_target_name(current, parent_path/t);
    if (k==nullptr) {
      add(t.string(), current, force);
      current = find_by_target_name(current, parent_path/t);
    } else {
      current = k;
    }
    parent_path /= t;
  }
  auto source_name = std::filesystem::path(current->source_name)/make_source_name_from_target_name(filename);
  if (auto l = find_by_source_name(current, source_name); l!=nullptr && !force) {
    std::cerr << fmt::format("{} already added. Add the -f flag to force", l->target_name) << std::endl;
    exit(1);
  }
  std::shared_ptr<entry> t;
  if (fs::is_directory(target_dir/target)) {
    t = std::make_shared<dir_entry>(target, source_name, current,
                                    false,
                                    false);
    fs::create_directory(source_dir/t->source_name, target_dir/t->target_name);

  } else if (fs::is_regular_file(target_dir/target)) {
    t = std::make_shared<file_entry>(target, source_name, current,
                                     false,
                                     false);
    fs::copy(target_dir/t->target_name, source_dir/t->source_name, fs::copy_options::update_existing);

  } else {
    std::cerr << "WHAT" << std::endl;
    exit(1);
  }
  current->entries.push_back(t);
}
void source_state::add_path(const std::string &target, std::shared_ptr<entry> current, bool force) {
  auto target_rel_path = std::filesystem::relative(target, target_dir);

  add(target_rel_path, std::move(current), force);
}
void source_state::print() {
  source_dir_entry->print();
}

std::string source_state::make_target_name_from_source_name(std::string source_name) {
  if (source_name.find(home_sweet_home::suffix::suffix_delimiter)==std::string::npos)
    return source_name;
  auto suffixes = home_sweet_home::suffix::get_suffix_list(source_name);
  auto actual_name = home_sweet_home::suffix::remove_suffixes(source_name);
  if (ranges::find(suffixes, home_sweet_home::suffix::hidden_suffix)!=ranges::end(suffixes)) {
    actual_name = "." + actual_name;
  }
  return actual_name;
}
std::string source_state::make_source_name_from_target_name(const std::string& target_name) {
  if (target_name.starts_with(".")) {
    return fmt::format("{}{}{}",
                       target_name.substr(1),
                       home_sweet_home::suffix::suffix_delimiter,
                       home_sweet_home::suffix::hidden_suffix);
  }
  return target_name;
}
std::string source_state::get_target_name(const std::string &source_name) {
  std::filesystem::path p;
  for(auto &t: std::filesystem::relative(source_name, source_dir)) {
    p /= make_target_name_from_source_name(t);
  }

  return p;
}
void source_state::populate() {
  for(const auto &t: std::filesystem::recursive_directory_iterator(source_dir)) {
    auto rel_path = std::filesystem::relative(t, source_dir);
    populate(rel_path, nullptr);
  }
}
void source_state::populate(const std::string &source, std::shared_ptr<entry> current) {
  auto parent = std::filesystem::path(source).parent_path();
  auto filename = std::filesystem::path(source).filename();
  std::filesystem::path parent_path;
  if(current ==nullptr) current = source_dir_entry;
  for(auto &t: parent) {
    auto k = find_by_source_name(current, parent_path / t);
    if(k == nullptr) {
      populate(t.string(), current);
      current = find_by_source_name(current, parent_path / t);
    } else {
      current = k;
    }
    parent_path /= t;
  }

  std::shared_ptr<entry> t;
  if(fs::is_directory(source_dir / source)) {
    t = std::make_shared<dir_entry>( std::filesystem::path(current->target_name) / make_target_name_from_source_name(filename), source, current,
                                     false,
                                     false);
  } else if(fs::is_regular_file(source_dir / source)) {
    t = std::make_shared<file_entry>( std::filesystem::path(current->target_name) / make_target_name_from_source_name(filename), source, current,
                                     false,
                                     false);
  } else {
    std::cerr << "WHAT" << std::endl;
    exit(1);
  }
  current->entries.push_back(t);
}
json source_state::dump_json() {
  return source_dir_entry->to_json();
}
YAML::Node source_state::dump_yaml() {
  return source_dir_entry->to_yaml();
}
std::shared_ptr<entry> source_state::locate_entry(std::string target_name) const {
  auto rel_path = fs::relative(target_name, target_dir);
  fs::path parent_path;
  auto current = source_dir_entry;
  for(auto &p: fs::path(rel_path)) {
    auto k = find_by_target_name(current, parent_path / p);
    if(k ==nullptr) {
      std::cerr << "Not added" << std::endl;
      exit(1);
    }

    current = k;
    parent_path /= p;
  }

  return current;
}
