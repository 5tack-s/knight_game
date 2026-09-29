cmake_minimum_required(VERSION 3.16)
project(knight_game LANGUAGES CXX)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(FETCHCONTENT_QUIET OFF)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif()


set(SDLTTF_VENDORED ON)
set(SDLTTF_HARFBUZZ OFF)
set(SDLTTF_PLUTOSVG OFF)

FetchContent_Declare(
SDL3
URL https://github.com/libsdl-org/SDL/releases/download/release-3.4.16/SDL3-3.4.16.tar.gz
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
SDL3_ttf
GIT_TAG release-3.2.2
GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
GIT_SHALLOW TRUE
GIT_SUBMODULES external/freetype
)

FetchContent_Declare(
SDL3_mixer
URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-3.2.4/SDL3_mixer-3.2.4.tar.gz
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
SDL3_image
URL https://github.com/libsdl-org/SDL_image/releases/download/release-3.4.6/SDL3_image-3.4.6.tar.gz
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


FetchContent_MakeAvailable(SDL3 SDL3_image SDL3_mixer SDL3_ttf)

add_subdirectory(src/deck/)
add_subdirectory(src/game/)
