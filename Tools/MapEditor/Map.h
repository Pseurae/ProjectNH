#pragma once

#include <string>
#include <vector>
#include "Tilemap.h"
#include "Tileset.h"

class Map
{
public:
    void Load(const std::string &fname);
    void Save(const std::string &fname);

    const auto &GetName() const { return mName; }
    auto GetWidth() const { return mWidth; }
    auto GetHeight() const { return mHeight; }

    auto &GetTileset() { return mTileset; }
    auto &GetTilemaps() { return mTilemaps; }

private:
    std::string mName;
    int mWidth, mHeight;
    Tileset mTileset;
    std::vector<Tilemap> mTilemaps;
    std::vector<unsigned char> mCollision;
};