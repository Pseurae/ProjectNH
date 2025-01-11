project(Tools)

add_executable(${PROJECT_NAME} main.cpp Window.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui opengl32 fmt)