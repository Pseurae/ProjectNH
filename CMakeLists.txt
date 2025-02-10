cmake_minimum_required(VERSION 3.5)
project(ProjectNH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_subdirectory(ThirdParty)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

set(ENGINE_SOURCE 
    Engine/Controls.cpp 
    Engine/Entry.cpp 
    Engine/Game.cpp 
    Engine/EntityState.cpp 
    Engine/Map.cpp
    Engine/PlayerRenderer.cpp
    Engine/PlayerState.cpp
    Engine/Tool.cpp

    Engine/Loaders/Binary.cpp
    Engine/Loaders/Texture.cpp
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC Engine)
target_link_libraries(${PROJECT_NAME} Ethyl Tonic tomlplusplus::tomlplusplus stb_image imgui)

add_executable(${PROJECT_NAME}Editor ${ENGINE_SOURCE})
target_include_directories(${PROJECT_NAME}Editor PUBLIC Engine)
target_link_libraries(${PROJECT_NAME}Editor Ethyl Tonic tomlplusplus::tomlplusplus stb_image imgui)
target_compile_definitions(${PROJECT_NAME}Editor PUBLIC NH_EDITOR)
