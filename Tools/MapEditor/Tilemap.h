#pragma once

#include <string>
#include <vector>

class Tilemap
{
public:
    Tilemap(int width, int height) : mWidth(width), mHeight(height)
    {}

    auto &GetWidth() { return mWidth; }
    auto &GetHeight() { return mHeight; }
    auto &GetTiles() { return mTiles; }
    auto &GetZOrder() { return mZOrder; }

private:
    int mWidth, mHeight;
    std::vector<unsigned short> mTiles;
    int mZOrder;
};