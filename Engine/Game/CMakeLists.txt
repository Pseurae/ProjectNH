add_executable(Game 
    Entry.cpp
    Game.cpp
)

target_link_libraries(Game PUBLIC Common)
target_include_directories(Game PUBLIC .)