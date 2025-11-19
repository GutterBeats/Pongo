cmake_minimum_required(VERSION 4.0)
project(Pongo)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

set(SDLMIXER_VENDORED ON)
set(SDLTTF_VENDORED ON)
set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor")

# SDL
FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL)

# SDL_image
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL_image)

# SDL_ttf
FetchContent_Declare(
        SDL_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL_ttf)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/Game.cpp
        src/core/Game.h
        src/core/ResourceManager.cpp
        src/core/ResourceManager.h
        src/core/Assets.h
        src/core/AudioSystem.cpp
        src/core/AudioSystem.h
        src/core/Utils.h
        src/core/Window.cpp
        src/core/Window.h
        src/levels/MainMenu.cpp
        src/levels/MainMenu.h
        src/core/Level.h
)
target_include_directories(${PROJECT_NAME} PRIVATE src assets ${VENDOR_DIR}/SDL_mixer/include)

add_subdirectory("vendor/SDL_mixer")

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)
