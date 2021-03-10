

# Tests need to be added as executables first
add_executable(tests
        main.cpp
        test_attr.cpp
)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(tests PRIVATE core)
target_link_libraries(tests PRIVATE ${LIBGIT2_LIBRARIES} ${CONAN_LIBS})

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME tests COMMAND tests) # command can be a target
