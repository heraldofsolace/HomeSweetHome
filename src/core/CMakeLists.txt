add_library(core STATIC
        app.h
        attr.h
        config.h
        config.cpp
        attr.cpp
        app.cpp
        utilities.h
        utilities.cpp target_state.cpp target_state.h entry.cpp entry.h)
create_target_directory_groups(core)
target_link_libraries(core PUBLIC ${LIBGIT2_LIBRARIES} ${CONAN_LIBS})