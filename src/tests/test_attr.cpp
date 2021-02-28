//
// Created by aniket on 16/02/2021.
//

#include <catch2/catch.hpp>
#include <core/attr.h>
#include <sstream>
#include <fstream>
namespace fs = std::filesystem;
std::string demo_perms(fs::perms p)
{
  std::stringstream ss;
  ss << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
            << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
            << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-");
  return ss.str();
}

TEST_CASE("dir_attr should behave correctly") {
  SECTION("dir_attr sets the correct names") {
    dir_attr d{"private_test"};
    REQUIRE(d.source_name == "private_test");
    REQUIRE(d.target_name == "test");
    REQUIRE(demo_perms(d.perm()) == "rwx------");


    dir_attr d2{"dot_test"};
    REQUIRE(d2.source_name == "dot_test");
    REQUIRE(d2.target_name == ".test");
    REQUIRE(demo_perms(d2.perm()) == "rwxrwxrwx");
  }
}

TEST_CASE("file_attr should behave correctly") {
  SECTION("file_attr sets the correct names") {
    file_attr f{"private_test"};
    REQUIRE(f.source_name == "private_test");
    REQUIRE(f.target_name == "test");
    REQUIRE(demo_perms(f.perm()) == "rw-------");


    file_attr f2{"dot_test"};
    REQUIRE(f2.source_name == "dot_test");
    REQUIRE(f2.target_name == ".test");
    REQUIRE(demo_perms(f2.perm()) == "rw-rw-rw-");
  }
}