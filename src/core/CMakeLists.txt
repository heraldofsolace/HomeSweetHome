add_library(core STATIC
        app.h
        config.h
        config.cpp
        app.cpp
        utilities.h
        utilities.cpp source_state.cpp source_state.h entry.cpp entry.h exceptions.h shell_command.cpp shell_command.h modifier.cpp modifier.h path_formatter.h template_data.cpp template_data.h template_engine.cpp template_engine.h)
create_target_directory_groups(core)
target_link_libraries(core PUBLIC ${LIBGIT2_LIBRARIES} ${CONAN_LIBS})