#pragma once

#include "Tileset.h"

class Map
{
public:
    void Load(const std::string &fname);
    void Save(const std::string &fname);
private:
    Tileset mTileset;
};