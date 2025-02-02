project(Common)

add_library(${PROJECT_NAME} STATIC main.cpp Window.cpp EventBus.cpp Texture.cpp FileDialog.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui opengl32 fmt Tonic stb_image nfd)
target_include_directories(${PROJECT_NAME} PUBLIC .)