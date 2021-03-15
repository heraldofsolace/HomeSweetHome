# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.17.5)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(dtl-populate NONE)

include(ExternalProject)
ExternalProject_Add(dtl-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/cubicdaiya/dtl.git" "GIT_TAG" "master"
                    SOURCE_DIR          "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src"
                    BINARY_DIR          "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
