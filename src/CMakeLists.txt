include_directories(${GIT2_INCLUDE_DIR})
include_directories(${dtl_SOURCE_DIR}/dtl)
include_directories(.)

add_subdirectory(core)
add_subdirectory(app)
add_subdirectory(tests)