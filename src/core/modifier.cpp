//
// Created by aniket on 10/03/2021.
//
#include <fstream>
#include <fmt/core.h>
#include <fmt/color.h>
#include "modifier.h"
#include "path_formatter.h"
void filesystem_modifier::create_directories(fs::path path) {
  fs::create_directories(path);
}
void filesystem_modifier::create_file(fs::path path, std::string text) {
  std::ofstream file(path);
  file << text;
  file.close();
}
void filesystem_modifier::copy_file(fs::path from, fs::path to, fs::copy_options options) {
  fs::copy(from, to, options);
}
void filesystem_modifier::delete_file(fs::path path) {
  fs::remove(path);
}
void filesystem_modifier::create_directory(fs::path path, fs::path attributes) {
  fs::create_directory(path, attributes);
}
void filesystem_modifier::execute_template(fs::path path, fs::path to) {
  std::ifstream fs(path);
  auto result = engine.render(fs);
  std::ofstream of(to);
  of << result;
  of.close();
}
void dry_run_modifier::create_directories(fs::path path) {
  fmt::print("Creating directory: {}\n", path);
}
void dry_run_modifier::create_file(fs::path path, std::string text) {
  fmt::print("Creating file {} with content {}\n", path, text.size() > 200 ? text.substr(0, 200) + "..." : text);
}
void dry_run_modifier::copy_file(fs::path from, fs::path to, fs::copy_options options) {
  fmt::print(fmt::fg(fmt::color::blue), "Copying {} to {}\n", from, to);
}
void dry_run_modifier::delete_file(fs::path path) {
  fmt::print("Deleting {}\n", path);
}
void dry_run_modifier::create_directory(fs::path path, fs::path attributes) {
  fmt::print("Creating directory {} with same attributes as {}\n", path, attributes);
}
void dry_run_modifier::execute_template(fs::path path, fs::path to) {
  fmt::print("Executing template {} and storing in {}\n", path, to);
}
void logging_modifier::create_directories(fs::path path) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Creating directory: {}\n", path);
  actual_modifier->create_directories(path);
  log.close();
}
void logging_modifier::create_file(fs::path path, std::string text) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Creating file {} with content {}\n", path, text);
  actual_modifier->create_file(path, text);
  log.close();
}
void logging_modifier::copy_file(fs::path from, fs::path to, fs::copy_options options) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Copying {} to {}\n", from, to);
  actual_modifier->copy_file(from, to, options);
  log.close();
}
void logging_modifier::delete_file(fs::path path) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Deleting {}\n", path);
  actual_modifier->delete_file(path);
  log.close();
}
void logging_modifier::create_directory(fs::path path, fs::path attributes) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Creating directory {} with same attributes as {}\n", path, attributes);
  actual_modifier->create_directory(path, attributes);
  log.close();
}
void logging_modifier::execute_template(fs::path path, fs::path to) {
  std::ofstream log(log_path, std::ios::app);
  log << fmt::format("Executing template {}\n", path);
  actual_modifier->execute_template(path, to);
  log.close();
}

