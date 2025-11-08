cmake_minimum_required(VERSION 4.0)
project(Pongo)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

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

# Glaze
FetchContent_Declare(
        glaze
        GIT_REPOSITORY https://github.com/stephenberry/glaze.git
        GIT_TAG main
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glaze)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/Game.cpp
        src/core/Game.h
        src/core/Layer.cpp
        src/core/Layer.h
        src/core/Entity.cpp
        src/core/Entity.h
        src/gameplay/Layers/MainMenu.cpp
        src/gameplay/Layers/MainMenu.h
        src/core/ResourceManager.cpp
        src/core/ResourceManager.h
        assets/Assets.h
        src/core/AudioSystem.cpp
        src/core/AudioSystem.h
        src/core/Utils.h)

target_include_directories(${PROJECT_NAME} PRIVATE src assets ${VENDOR_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE "${VENDOR_DIR}/fmod/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        glaze::glaze
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} PRIVATE fmodL)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE fmod)
endif ()

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)
