#pragma once

#include "Map.h"
#include "Brush.h"

enum class Mode : unsigned char
{
    Tilemap,
    Sprites,
    Entity,
};

struct Context
{
    Map map;
    Brush brush;
    Mode mode = Mode::Tilemap;
};

extern Context gContext;