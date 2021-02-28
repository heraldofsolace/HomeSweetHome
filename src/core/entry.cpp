//
// Created by aniket on 27/02/2021.
//

#include "entry.h"
#include "app.h"
#include <string>
std::string dir_entry::make_sourcename(std::string name, std::string parent_source_name, bool _private) {
  std::string source_name;
  if(_private) {
    source_name += home_sweet_home::prefix::private_prefix;
  }

  if(home_sweet_home::prefix::has_prefix(name, ".")) {
    source_name += std::string(home_sweet_home::prefix::dot_prefix) + home_sweet_home::prefix::must_trim_prefix(name, ".");
  } else {
    source_name += name;
  }

  return parent_source_name + source_name;
}
void dir_entry::get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) {
  entry::get_entries(entries, name);
}
std::tuple<std::string, bool> dir_entry::make_targetname(std::string name) {
  bool is_private = false;
  bool is_exact = false;

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::private_prefix)) {
    name = home_sweet_home::prefix::must_trim_prefix(name,  home_sweet_home::prefix::private_prefix);
    is_private = true;
  }

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::dot_prefix)) {
    name = "." + home_sweet_home::prefix::must_trim_prefix(name,  home_sweet_home::prefix::dot_prefix);
  }

  return std::make_tuple(name, is_private);
}


std::vector<std::tuple<std::string, bool>> dir_entry::make_dir_targetnames(std::string name) {
  std::vector<std::tuple<std::string, bool>> vec;

  for(const auto& it: std::filesystem::path(name)) {
    vec.push_back(dir_entry::make_targetname(it.string()));

  }
  return vec ;
}
std::string file_entry::make_sourcename(std::string name, std::string parent_source_name, bool _private) {
  std::string source_name;
  if(_private) {
    source_name += home_sweet_home::prefix::private_prefix;
  }
  if(home_sweet_home::prefix::has_prefix(name, ".")) {
    source_name += std::string(home_sweet_home::prefix::dot_prefix) + home_sweet_home::prefix::must_trim_prefix(name, ".");
  } else {
    source_name += name;
  }

  return parent_source_name + source_name;
}
void file_entry::get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) {
  entry::get_entries(entries, name);
}
std::tuple<std::string, bool> file_entry::make_targetname(std::string name) {

  bool is_empty = false, is_encrypted =  false, is_executable = false, is_once = false, is_private = false, is_template = false;
  int order = 0;

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::create_prefix)) {
   // type = source_filetype::SOURCE_FILE_TYPE_CREATE;
    name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::create_prefix);

    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::encrypted_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::encrypted_prefix);
      is_encrypted = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::private_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::private_prefix);
      is_private = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::executable_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::executable_prefix);
      is_executable = true;
    }
  } else if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::run_prefix)) {
    //type = source_filetype::SOURCE_FILE_TYPE_SCRIPT;
    name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::run_prefix);

    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::once_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::once_prefix);
      is_once = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::before_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::before_prefix);
      order = -1;
    }
    else if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::after_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::after_prefix);
      order = 1;
    }
  } else if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::symlink_prefix)) {
    //type = source_filetype::SOURCE_FILE_TYPE_SYMLINK;
    name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::symlink_prefix);

  } else if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::modify_prefix)) {
   // type = source_filetype::SOURCE_FILE_TYPE_MODIFY;
    name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::modify_prefix);
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::private_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::private_prefix);
      is_private = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::executable_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::executable_prefix);
      is_executable = true;
    }
  } else {
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::encrypted_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::encrypted_prefix);
      is_encrypted = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::private_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::private_prefix);
      is_private = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::empty_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::empty_prefix);
      is_empty = true;
    }
    if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::executable_prefix)) {
      name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::executable_prefix);
      is_executable = true;
    }
  }
  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::dot_prefix)) {
    name = "." + home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::dot_prefix);
  }

  if(home_sweet_home::suffix::has_suffix(name, home_sweet_home::suffix::template_suffix)) {
    name = home_sweet_home::suffix::must_trim_suffix(name, home_sweet_home::suffix::template_suffix);
    is_template = true;
  }

  return std::make_tuple(name, is_private);
}
