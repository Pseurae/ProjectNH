#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Texture.h"

class Tileset
{
public:
    void Load(const std::string &fname);
    void Save(const std::string &fname);

    auto GetWidth() const { return mWidth; }
    auto GetHeight() const { return mHeight; }

    const auto &GetPath() const { return mPath; }
    auto &GetTexture() { return mTilesetTexture; }

private:
    std::string mPath;
    std::shared_ptr<Texture> mTilesetTexture;
    std::vector<unsigned char> mCollision;
    int mWidth, mHeight;
};