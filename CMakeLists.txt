cmake_minimum_required(VERSION 3.16)
project(particle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)
find_package(OpenMP REQUIRED)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
        "src/*.c"
        "include/raygui.h"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib glm OpenMP::OpenMP_CXX)