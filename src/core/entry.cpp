//
// Created by aniket on 27/02/2021.
//

#include "entry.h"
#include "app.h"

using entries::entry;

json entries::dir_entry::to_json() {
  json j = {
      { "type", "dir" },
      { "is_private", is_private },
      { "is_exact", is_exact },
      { "source_name", source_name },
      { "target_name", target_name }
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
  out << YAML::Key << "is_private" << YAML::Value << is_private;
  out << YAML::Key << "is_exact" << YAML::Value << is_exact;
  out << YAML::Key << "source_name" << YAML::Value << source_name;
  out << YAML::Key << "target_name" << YAML::Value << target_name;

  std::vector<YAML::Node> entries_yaml;
  for(auto &e: entries) {
    entries_yaml.push_back(e->to_yaml());
  }
  out << YAML::Key << "entries" << YAML::Value;
  out << YAML::BeginSeq;
  for(auto &t: entries_yaml) {
    out << t;
  }
  out << YAML::EndSeq;
  out << YAML::EndMap;

  YAML::Node node = YAML::Load(out.c_str());

  return node;
}
json entries::file_entry::to_json() {
  json j = {
      { "type", "file" },
      { "is_private", is_private },
      { "source_name", source_name },
      { "target_name", target_name }
  };

  return j;
}
YAML::Node entries::file_entry::to_yaml() {
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "type" << YAML::Value << "file";
  out << YAML::Key << "is_private" << YAML::Value << is_private;
  out << YAML::Key << "source_name" << YAML::Value << source_name;
  out << YAML::Key << "target_name" << YAML::Value << target_name;

  out << YAML::EndMap;

  YAML::Node node = YAML::Load(out.c_str());

  return node;
}
