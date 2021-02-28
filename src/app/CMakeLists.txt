add_executable(
        home_sweet_home
        main.cpp
        cmd_init.h
        cmd_init.cpp
        cmd_add.cpp cmd_add.h)

create_target_directory_groups(home_sweet_home)
target_link_libraries(home_sweet_home PRIVATE core)