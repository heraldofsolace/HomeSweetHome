add_library(core STATIC
        app.h
        config.h
        config.cpp
        app.cpp
        utilities.h
        utilities.cpp source_state.cpp source_state.h entry.cpp entry.h exceptions.h)
create_target_directory_groups(core)
target_link_libraries(core PUBLIC ${LIBGIT2_LIBRARIES} ${CONAN_LIBS})