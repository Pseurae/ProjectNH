project(MapEditor)

add_executable(${PROJECT_NAME} MapEditor.cpp Map.cpp Tilemap.cpp Tileset.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Common)