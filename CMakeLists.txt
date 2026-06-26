cmake_minimum_required(VERSION 3.21)

project(TextEditor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TEXTEDITOR_BUILD_TESTS "Build unit tests" ON)

include(FetchContent)

# ============================================================
# SDL3
# ============================================================

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.16
)

# ============================================================
# SDL3_ttf
# ============================================================

FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
)

# ============================================================
# Catch2
# ============================================================

if(TEXTEDITOR_BUILD_TESTS)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.10.0
    )
endif()

FetchContent_MakeAvailable(SDL3 SDL3_ttf)

if(TEXTEDITOR_BUILD_TESTS)
    FetchContent_MakeAvailable(Catch2)
endif()

# ============================================================
# Library Sources
# ============================================================

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
)

# Remove main.cpp from library
list(REMOVE_ITEM APP_SOURCES
    "${CMAKE_SOURCE_DIR}/source/main.cpp"
)

# ============================================================
# Core Library
# ============================================================

add_library(TextEditorLib
    ${APP_SOURCES}
)

target_link_libraries(TextEditorLib
    PUBLIC
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)

target_include_directories(TextEditorLib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# ============================================================
# Main Application
# ============================================================

add_executable(TextEditor
    source/main.cpp
)

target_link_libraries(TextEditor
    PRIVATE
        TextEditorLib
)

# ============================================================
# Warnings
# ============================================================

if(MSVC)

    target_compile_options(TextEditorLib PRIVATE
        /W4
    )

else()

    target_compile_options(TextEditorLib PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -g
    )

endif()

# ============================================================
# Tests
# ============================================================

if(TEXTEDITOR_BUILD_TESTS)

    include(CTest)
    enable_testing()

    add_subdirectory(tests)

endif()

