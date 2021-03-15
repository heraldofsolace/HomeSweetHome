#include "core/config.h"
#include "core/source_state.h"
#include <vector>

namespace home_sweet_home::cmd {
using home_sweet_home::config::Config;
struct CmdForgetOptions {
  bool force;
  bool remove;
  std::vector<std::string> targets;
  //TODO Add rest
};
void setup_cmd_forget(CLI::App &app, Config const &config);
void run_cmd_forget(CmdForgetOptions const &opt, Config const &config);

}