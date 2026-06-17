cmake_minimum_required(VERSION 3.21)

project(TextEditor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.16   # Use a specific release
)

# SDL3_ttf
FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2    # Use a specific release
)

FetchContent_MakeAvailable(SDL3 SDL3_ttf)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
)

add_executable(TextEditor
    ${SOURCES}
)

target_link_libraries(TextEditor
    PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)

if(MSVC)
    target_compile_options(TextEditor PRIVATE /W4)
else()
    target_compile_options(TextEditor PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()


# Configure once
# cmake -B build

# Build
# cmake --build build

# After editing code
# cmake --build build

# After changing CMakeLists.txt
# cmake -B build
# cmake --build build
