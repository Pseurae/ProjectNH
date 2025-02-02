#pragma once

#include "Application.h"
#include "Map.h"

class MapEditor final : public Application
{
public:
    MapEditor();
    ~MapEditor();

    WindowDesc GetWindowDesc() final;
    void Frame();
    
    void MainMenuBar();
    void TilemapMode();
};