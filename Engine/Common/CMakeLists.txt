add_library(Common STATIC
    Loaders/Binary.cpp
    Loaders/Texture.cpp

    Controls.cpp 
    EntityState.cpp 
    Map.cpp
    PlayerRenderer.cpp
    PlayerState.cpp
)
target_include_directories(Common PUBLIC .)
target_link_libraries(Common PUBLIC Ethyl Tonic tomlplusplus::tomlplusplus stb_image imgui)
