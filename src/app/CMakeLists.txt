add_executable(
        home_sweet_home
        main.cpp
        cmd_init.h
        cmd_init.cpp
        cmd_add.cpp cmd_add.h cmd_dump.cpp cmd_dump.h cmd_edit.cpp cmd_edit.h cmd_diff.cpp cmd_diff.h cmd_apply.cpp cmd_apply.h cmd_data.h cmd_data.cpp cmd_template.h cmd_forget.h cmd_forget.cpp)

create_target_directory_groups(home_sweet_home)
target_link_libraries(home_sweet_home PRIVATE core)