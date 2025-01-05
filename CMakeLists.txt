cmake_minimum_required(VERSION 3.5)
project(ProjectNH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_subdirectory(ThirdParty)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} 
    Engine/Entry.cpp 
    Engine/Game.cpp 
    Engine/Controls.cpp 
    Engine/EntityState.cpp 
    Engine/PlayerState.cpp
    Engine/PlayerRenderer.cpp)
target_link_libraries(${PROJECT_NAME} Ethyl Tonic tomlplusplus::tomlplusplus stb_image)
