cmake_minimum_required(VERSION 3.16)
project(knight_game LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL3)
find_package(SDL3_image)
find_package(SDL3_mixer)
find_package(SDL3_ttf)

file(GLOB GAME_SOURCE CONFIGURE_DEPENDS "src/game/*.cpp")
file(GLOB GAME_UTILS CONFIGURE_DEPENDS "src/game/utils/*.cpp")
file(GLOB_RECURSE ENGINE_SOURCE CONFIGURE_DEPENDS "src/deck/*.cpp")

include_directories(src/deck/)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${GAME_SOURCE}
    ${ENGINE_SOURCE}
    ${GAME_UTILS}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)