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
#include <variant>
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

void source_state::add(const std::string &target,
                       std::shared_ptr<entry> current,
                       bool force,
                       bool tmpl,
                       std::shared_ptr<modifier> mod) {

  auto parent = std::filesystem::path(target).parent_path();
  auto filename = std::filesystem::path(target).filename();
  if (current==nullptr)
    current = source_dir_entry;
  std::filesystem::path parent_path;
  for (auto &t: parent) {
    auto k = find_by_target_name(current, parent_path/t);
    if (k==nullptr) {
      add(t.string(), current, force,  tmpl, mod);
      current = find_by_target_name(current, parent_path/t);
    } else {
      current = k;
    }
    parent_path /= t;
  }
  auto source_name = std::filesystem::path(current->source_name)/make_source_name_from_target_name(filename);
  if(tmpl) source_name += ".tmpl";
  if (auto l = find_by_source_name(current, source_name); l!=nullptr && !force) {
    std::cerr << fmt::format("{} already added. Add the -f flag to force", l->target_name) << std::endl;
    exit(1);
  }
  std::shared_ptr<entry> t;
  if (fs::is_directory(target_dir/target)) {
    t = std::make_shared<dir_entry>(target, source_name, current,
                                    false,
                                    false);
    mod->create_directory(source_dir/t->source_name, target_dir/t->target_name);

  } else if (fs::is_regular_file(target_dir/target)) {
    t = std::make_shared<file_entry>(target, source_name, current,
                                     false,
                                     false);
    mod->copy_file(target_dir/t->target_name, source_dir/t->source_name, fs::copy_options::update_existing);

  } else {
    std::cerr << "WHAT" << std::endl;
    exit(1);
  }
  current->entries.push_back(t);
}
void source_state::add_path(const std::string &target,
                            std::shared_ptr<entry> current,
                            bool force,
                            bool tmpl,
                            std::shared_ptr<modifier> mod) {
  auto target_rel_path = std::filesystem::relative(target, target_dir);

  add(target_rel_path, std::move(current), force, tmpl, std::move(mod));
}
void source_state::print() {
  source_dir_entry->print();
}

std::pair<std::string,
          std::variant<file_entry::file_entry_info,
                       dir_entry::dir_entry_info>> source_state::make_target_name_from_source_name(std::string source_name,
                                                                                                   bool is_dir) {
  std::variant<file_entry::file_entry_info, dir_entry::dir_entry_info> info;
  if (is_dir) {
    info = dir_entry::dir_entry_info{};
  } else {
    info = file_entry::file_entry_info{};
  }
  std::string name = source_name;
  if (!is_dir && source_name.ends_with(".tmpl")) {
    source_name = source_name.erase(source_name.size() - 5);
    std::get<file_entry::file_entry_info>(info).is_template = true;
  }
  if (source_name.find(home_sweet_home::suffix::suffix_delimiter)==std::string::npos)
    return std::make_pair(source_name, info);

  auto suffixes = home_sweet_home::suffix::get_suffix_list(source_name);
  auto actual_name = home_sweet_home::suffix::remove_suffixes(source_name);
  if (ranges::find(suffixes, home_sweet_home::suffix::hidden_suffix)!=ranges::end(suffixes)) {
    actual_name = "." + actual_name;
  }
  return std::make_pair(actual_name, info);
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
std::string source_state::get_target_name(const std::string &source_name) const {
  std::filesystem::path p;
  for(auto &t: std::filesystem::relative(source_name, source_dir)) {
    p /= make_target_name_from_source_name(t, false).first; // Don't care about type
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
    auto[name, info] = make_target_name_from_source_name(filename, true);
    t = std::make_shared<dir_entry>(std::filesystem::path(current->target_name)/name, source, current,
                                    std::get<dir_entry::dir_entry_info>(info).is_private,
                                    std::get<dir_entry::dir_entry_info>(info).is_exact);
  } else if(fs::is_regular_file(source_dir / source)) {
    auto[name, info] = make_target_name_from_source_name(filename, false);

    t = std::make_shared<file_entry>(std::filesystem::path(current->target_name)/name, source, current,
                                     std::get<file_entry::file_entry_info>(info).is_private,
                                     std::get<file_entry::file_entry_info>(info).is_template);
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
std::shared_ptr<entry> source_state::locate_entry(const std::string& target_name) const {
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
void source_state::apply(const std::shared_ptr<modifier> &mod, const std::shared_ptr<entry> &e) const {
  e->apply(source_dir, target_dir, mod);
}
void source_state::apply(const std::shared_ptr<modifier> &mod, const std::string &target_name, bool recursive) {
  if (target_name.empty()) {
    source_dir_entry->apply(source_dir, target_dir, mod);
  } else {
    auto k = locate_entry(target_name);
    if (k==nullptr) {
      std::cerr << "Is not added" << std::endl;
      return;
    }
    k->apply_backwards(source_dir, target_dir, mod);
    if (recursive) {
      ranges::for_each(k->entries, [this, &mod](auto e) {
        e->apply(source_dir, target_dir, mod);
      });
    }

  }
}
void source_state::walk(const std::function<void(std::shared_ptr<entry>)>& func) {
  func(source_dir_entry);
  source_dir_entry->walk(func);
}
void source_state::put_templates(template_engine &te) {

  walk([this, &te](auto e) {

    if (e->source_name.empty() || e->target_name.empty())
      return;
    auto f = std::dynamic_pointer_cast<file_entry>(e);
    if (f && f->info.is_template) {

      auto result = te.get_env().parse_template(source_dir/f->source_name);
      te.get_env().include_template(e->source_name, result);
    }
  });

}
bool source_state::remove_entry(const std::string &target_name, bool remove, const std::shared_ptr<modifier> &mod) {
  auto k = locate_entry(target_name);
  if (!k)
    return false;
  mod->delete_file(source_dir/k->source_name);
  auto &entries = k->parent_entry.lock()->entries;
  entries |= ranges::actions::remove_if([this, &target_name](auto e) {
    return e->target_name==fs::relative(target_name, target_dir);
  });

  if (remove) {
    mod->delete_file(target_dir/k->target_name);
  }

  return true;
}

