//
// Created by aniket on 11/03/2021.
//

#include <filesystem>
#include <vector>
#include <range/v3/all.hpp>
#include <fstream>
#include <regex>
#include <iostream>
#include "template_data.h"
#include "shell_command.h"

template_data::template_data(const config &conf) {
  data["home_dir"] = conf.homedir;
  data["username"] = conf.username;
  data["source_dir"] = conf.source;
  data["target_dir"] = conf.destination;

  data["kernel"] = get_kernel_info();
  data["os"] = get_os_info();

}
json template_data::get_kernel_info() {
  json kernel_data;
  std::filesystem::path procsyskernel{"/proc/sys/kernel"};
  if (std::filesystem::exists(procsyskernel) && std::filesystem::is_directory(procsyskernel)) {
    std::vector<std::string> files_to_read{"osrelease", "ostype", "version"};
    ranges::for_each(files_to_read, [&procsyskernel, &kernel_data](auto file) {
      std::ifstream fs(procsyskernel/file);
      std::string value;
      std::getline(fs, value);

      kernel_data[file] = value;
    });
  }

  return kernel_data;
}
json template_data::get_os_info() {
  json os_data;
  std::regex leading_ws("^\\s+");
  std::vector<std::string> files_to_read{"/etc/os-release", "/usr/lib/os-release"};
  ranges::for_each(files_to_read, [&os_data, &leading_ws](auto file) {
    if (std::filesystem::exists(file)) {
      std::ifstream fs(file);
      std::string line;
      while (std::getline(fs, line)) {
        auto trimmed = std::regex_replace(line, leading_ws, "");
        if (trimmed.empty() || trimmed[0]=='#') {
          continue;
        }
        auto fields = trimmed | ranges::views::split('=') | ranges::to<std::vector<std::string>>();
        if (fields.size()!=2) {
          std::cerr << "WHAT" << std::endl;
          exit(1);
        }
        std::string key = fields[0];
        std::string value;
        if (fields[1].starts_with('"') | fields[1].starts_with("'")) {
          value = fields[1].substr(1, fields[1].size() - 2);
        } else {
          value = fields[1];
        }

        os_data[key] = value;
      }
    }
  });

  return os_data;
}
json template_data::get_data() {
  return data;
}
