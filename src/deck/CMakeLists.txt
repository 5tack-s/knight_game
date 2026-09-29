add_library(deck
entity.cpp
mix.cpp
text.cpp
window.cpp
)


target_link_libraries(deck PUBLIC SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)
target_include_directories(deck PUBLIC .)
