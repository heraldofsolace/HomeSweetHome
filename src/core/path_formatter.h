//
// Created by aniket on 11/03/2021.
//

#ifndef HOMESWEETHOME_SRC_CORE_PATH_FORMATTER_H
#define HOMESWEETHOME_SRC_CORE_PATH_FORMATTER_H
#include <fmt/format.h>
#include <filesystem>

namespace fs = std::filesystem;
template<> struct fmt::formatter<fs::path> : formatter<std::string_view> {
  template<class FormatContext>
  auto format(const fs::path &path, FormatContext &ctx) {
    return formatter<std::string_view>::format(path.string(), ctx);
  }
};
#endif //HOMESWEETHOME_SRC_CORE_PATH_FORMATTER_H
