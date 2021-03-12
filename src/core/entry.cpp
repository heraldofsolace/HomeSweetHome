//
// Created by aniket on 27/02/2021.
//

#include "entry.h"
#include "app.h"

using entries::entry;

json entries::dir_entry::to_json() {
  json j = {
      {"type", "dir"},
      {"is_private", info.is_private},
      {"is_exact", info.is_exact},
      {"source_name", source_name},
      {"target_name", target_name}
  };

  std::vector<json> entries_json;
  for(auto &e: entries) {
    entries_json.push_back(e->to_json());
  }

  j["entries"] = entries_json;

  return j;
}
YAML::Node entries::dir_entry::to_yaml() {
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "type" << YAML::Value << "dir";
  out << YAML::Key << "is_private" << YAML::Value << info.is_private;
  out << YAML::Key << "is_exact" << YAML::Value << info.is_exact;
  out << YAML::Key << "source_name" << YAML::Value << source_name;
  out << YAML::Key << "target_name" << YAML::Value << target_name;

  std::vector<YAML::Node> entries_yaml;
  for (auto &e: entries) {
    entries_yaml.push_back(e->to_yaml());
  }
  out << YAML::Key << "entries" << YAML::Value;
  out << YAML::BeginSeq;
  for (auto &t: entries_yaml) {
    out << t;
  }
  out << YAML::EndSeq;
  out << YAML::EndMap;

  YAML::Node node = YAML::Load(out.c_str());

  return node;
}
void entries::dir_entry::apply(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
  mod->create_directory(target_dir/target_name, source_dir/source_name);
  entry::apply(source_dir, target_dir, mod);
}
void entries::dir_entry::apply_backwards(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
  entry::apply_backwards(source_dir, target_dir, mod);
  mod->create_directory(target_dir/target_name, source_dir/source_name);
}

json entries::file_entry::to_json() {
  json j = {
      {"type", "file"},
      {"is_private", info.is_private},
      {"source_name", source_name},
      {"target_name", target_name},
      {"is_template", info.is_template},
  };

  return j;
}
YAML::Node entries::file_entry::to_yaml() {
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "type" << YAML::Value << "file";
  out << YAML::Key << "is_private" << YAML::Value << info.is_private;
  out << YAML::Key << "source_name" << YAML::Value << source_name;
  out << YAML::Key << "target_name" << YAML::Value << target_name;

  out << YAML::EndMap;

  YAML::Node node = YAML::Load(out.c_str());

  return node;
}
void entries::file_entry::apply(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
  if (!info.is_template)
    mod->copy_file(source_dir/source_name, target_dir/target_name, fs::copy_options::update_existing);
  else
    mod->execute_template(source_dir/source_name, target_dir/target_name);
}
void entries::file_entry::apply_backwards(fs::path source_dir, fs::path target_dir, std::shared_ptr<modifier> mod) {
  entry::apply_backwards(source_dir, target_dir, mod);
  if (!info.is_template)
    mod->copy_file(source_dir/source_name, target_dir/target_name, fs::copy_options::update_existing);
  else
    mod->execute_template(source_dir/source_name, target_dir/target_name);
}
