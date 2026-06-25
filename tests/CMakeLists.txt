add_executable(EditorTests
    EditorTests.cpp
)

target_link_libraries(EditorTests
    PRIVATE
        TextEditorLib
        Catch2::Catch2WithMain
)

include(Catch)

catch_discover_tests(EditorTests)
