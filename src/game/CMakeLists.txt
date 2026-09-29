add_executable(
    ${CMAKE_PROJECT_NAME}
    character.cpp
    coin.cpp
    enemy.cpp
    main.cpp
    utils/constants.cpp
)

if(NOT EMSCRIPTEN)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ASSET_ROOT="${CMAKE_SOURCE_DIR}")
endif()

if(EMSCRIPTEN)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "--preload-file=${CMAKE_SOURCE_DIR}/assets@/assets")
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE deck)