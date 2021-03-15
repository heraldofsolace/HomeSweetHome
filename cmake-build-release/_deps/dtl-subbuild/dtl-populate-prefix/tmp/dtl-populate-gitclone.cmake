
if(NOT "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitinfo.txt" IS_NEWER_THAN "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/bin/git"  clone --no-checkout "https://github.com/cubicdaiya/dtl.git" "dtl-src"
    WORKING_DIRECTORY "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/cubicdaiya/dtl.git'")
endif()

execute_process(
  COMMAND "/bin/git"  checkout master --
  WORKING_DIRECTORY "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitinfo.txt"
    "/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/aniket/CLionProjects/home_sweet_home/cmake-build-release/_deps/dtl-subbuild/dtl-populate-prefix/src/dtl-populate-stamp/dtl-populate-gitclone-lastrun.txt'")
endif()

