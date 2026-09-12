cmake_minimum_required(VERSION 3.16)
project(particle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG v4.0.0
)

set(ENTT_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(EnTT)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.c"
    "include/raygui.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    RAYGUI_STATIC 
    RAYLIB_STATIC
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    glm 
    EnTT::EnTT
)

if(WIN32)
    add_compile_definitions(RAYGUI_DEF=extern)
    target_link_libraries(particle PRIVATE
        raylib
        opengl32
        gdi32
        winmm
        shell32
    )
endif()