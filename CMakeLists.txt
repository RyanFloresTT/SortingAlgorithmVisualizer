cmake_minimum_required(VERSION 3.28)
set(CMAKE_BUILD_TYPE Release)
project(SortingAlgorithmVisualizer)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
include(FetchContent)

set(SFML_VERSION 2.5.1)
set(IMGUI_VERSION 1.89)
# set(IMGUI_SFML_VERSION 2.3)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)

# Or by tag...
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG        2.6.x
        # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
        # ^ or like this - sometimes it's better because FetchContent won't look
        # into remote to see if branch head was updated or not - good for stable
        # tags like 'vX.X' corresponding to releases
)

## finally, let's build

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortingAlgorithmVisualizer "Source Files/main.cpp"
        "Header Files/SortingAlgorithms.h"
        "Source Files/SortingAlgorithms.cpp"
        "Header Files/Globals.h"
        "Source Files/Globals.cpp"
)

target_link_libraries(SortingAlgorithmVisualizer PUBLIC ImGui-SFML)