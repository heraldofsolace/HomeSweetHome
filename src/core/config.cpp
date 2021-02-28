//
// Created by aniket on 14/02/2021.
//

#include "config.h"
#include <cstdlib>
#include <cstring>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

namespace home_sweet_home::config {
Config::Config() {
  const char *_xdg_data_dir = std::getenv("XDG_DATA_HOME");
  const char *_xdg_config_dir = std::getenv("XDG_CONFIG_HOME");
  const char *_homedir = std::getenv("HOME");
  const char *_username = getpwuid(getuid()) -> pw_name;
  username = _username;
  if(!_homedir) {
    _homedir = getpwuid(getuid())->pw_dir;
  }
  homedir = _homedir;
  if(!_xdg_data_dir) {
    xdg_data_dir = homedir + "/.local/share";
  } else {
    xdg_data_dir = _xdg_data_dir;
  }

  if(!_xdg_config_dir) {
    xdg_config_dir = homedir + "/.config";
  }else {
    xdg_config_dir = _xdg_config_dir;
  }

  config_dir = xdg_config_dir + "/home_sweet_home";
  config_file = config_dir + "/home_sweet_home.ini";
  source = xdg_data_dir + "/home_sweet_home";
  destination = homedir;
}
}
