//
// Created by aniket on 15/02/2021.
//

#include "attr.h"

#include <utility>
#include "app.h"
dir_attr::dir_attr(std::string target_name, bool is_private) {
  std::cout << "dir target " << target_name << std::endl;
  this -> target_name = target_name;
  this -> is_private = is_private;
  is_exact = false;
  source_name = "";
  if(is_private) {
    source_name += home_sweet_home::prefix::private_prefix;
  }

  if(home_sweet_home::prefix::has_prefix(target_name, ".")) {
    source_name += std::string(home_sweet_home::prefix::dot_prefix) + home_sweet_home::prefix::must_trim_prefix(target_name, ".");
  } else {
    source_name += target_name;
  }

  std::filesystem::perms p = std::filesystem::perms::all;
  if(is_private) {
    p &= ~std::filesystem::perms::group_all;
    p &= ~std::filesystem::perms::others_all;
  }

  this->perm = p;
}

dir_attr::dir_attr(const std::string& source_name) {
  std::cout << "dir source " << source_name << std::endl;

  this -> source_name = source_name;
  is_private = false;
  is_exact = false;
  auto name = source_name;

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::private_prefix)) {
    name = home_sweet_home::prefix::must_trim_prefix(name,  home_sweet_home::prefix::private_prefix);
    is_private = true;
  }

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::dot_prefix)) {
    name = "." + home_sweet_home::prefix::must_trim_prefix(name,  home_sweet_home::prefix::dot_prefix);
  }

  std::filesystem::perms p = std::filesystem::perms::all;
  if(is_private) {
    p &= ~std::filesystem::perms::group_all;
    p &= ~std::filesystem::perms::others_all;
  }

  this->perm = p;
}


void dir_attr::get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) {
  for(auto& entry: this->entries) {

  }
}

file_attr::file_attr(std::string target_name, bool is_private) {
  std::cout << "file target " << target_name << std::endl;

  this -> target_name = target_name;
  type = source_filetype::SOURCE_FILE_TYPE_FILE;
  is_empty = is_encrypted =  is_executable = is_once  = is_template = false;
  order = 1;
  this->is_private = is_private;

  std::string name;
  if(is_private) {
    name += home_sweet_home::prefix::private_prefix;
  }
  if(home_sweet_home::prefix::has_prefix(target_name, ".")) {
    name += std::string(home_sweet_home::prefix::dot_prefix) + home_sweet_home::prefix::must_trim_prefix(target_name, ".");
  } else {
    name += target_name;
  }

  this -> source_name = name;
  std::filesystem::perms p = std::filesystem::perms::owner_read | std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::group_write | std::filesystem::perms::others_read | std::filesystem::perms::others_write;
  if(is_executable) {
    p |= std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec;
  }
  if(is_private) {
    p &= ~std::filesystem::perms::group_all;
    p &= ~std::filesystem::perms::others_all;
  }

  this->perm = p;

}
file_attr::file_attr(const std::string& source_name) {
  std::cout << "file source " <<  source_name << std::endl;

  this -> source_name = source_name;
  type = source_filetype::SOURCE_FILE_TYPE_FILE;
  std::string name = source_name;
  is_empty = is_encrypted =  is_executable = is_once = is_private = is_template = false;
  order = 0;

  if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::create_prefix)) {
    type = source_filetype::SOURCE_FILE_TYPE_CREATE;
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
    type = source_filetype::SOURCE_FILE_TYPE_SCRIPT;
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
    type = source_filetype::SOURCE_FILE_TYPE_SYMLINK;
    name = home_sweet_home::prefix::must_trim_prefix(name, home_sweet_home::prefix::symlink_prefix);

  } else if(home_sweet_home::prefix::has_prefix(name, home_sweet_home::prefix::modify_prefix)) {
    type = source_filetype::SOURCE_FILE_TYPE_MODIFY;
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

  target_name = name;

  std::filesystem::perms p = std::filesystem::perms::owner_read | std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::group_write | std::filesystem::perms::others_read | std::filesystem::perms::others_write;
  if(is_executable) {
    p |= std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec;
  }
  if(is_private) {
    p &= ~std::filesystem::perms::group_all;
    p &= ~std::filesystem::perms::others_all;
  }

  this->perm = p;
}
void file_attr::get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) {
  entry::get_entries(entries, name);
}
void entry::get_entries(std::unordered_map<std::string, std::unique_ptr<entry>> &entries, std::string name) {

}
