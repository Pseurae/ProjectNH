add_executable(ToolKit 
    Panes/Map.cpp
    Panes/Tilesets.cpp

    ToolKit.cpp
    Entry.cpp
)

target_link_libraries(ToolKit PUBLIC Common)
target_include_directories(ToolKit PUBLIC .)
