#pragma once

struct Brush
{
    enum Mode
    {
        Single,
        Rect,
        Fill
    };

    Mode mode;
    unsigned short currentTile;
};