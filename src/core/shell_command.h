//
// Created by aniket on 09/03/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_SHELL_COMMAND_H
#define HOMESWEETHOME_SRC_CORE_SHELL_COMMAND_H

#include <string>


class shell_command
{
public:
  int             exit_status = 0;
  std::string     command;
  std::string     std_in;
  std::string     std_out;
  std::string     std_err;

  void execute();
  explicit shell_command(std::string command, std::string std_in=""):
    command(std::move(command)), std_in(std::move(std_in)) {}

};

#endif //HOMESWEETHOME_SRC_CORE_SHELL_COMMAND_H
