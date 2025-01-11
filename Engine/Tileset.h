#pragma once

#include <Ethyl/Pointers.h>
#include <Tonic/Graphics/Texture.h>
#include <vector>
#include <string>

struct TilesetDesc
{
    std::string tiles, collision;
};

void LoadTilesetDescs(const std::string &fpath);

class Tileset
{
public:
    void Load(const std::string &name);
    void Load(const TilesetDesc &desc);

    auto GetSize() const { return glm::ivec2{ mXTiles, mYTiles }; }
    const auto &GetTexture() const { return mTexture; }
    const auto &GetCollision() const { return mCollision; }

private:
    std::string mName;
    int mXTiles = 0, mYTiles = 0;
    Ethyl::Shared<Tonic::Graphics::Texture> mTexture = nullptr;
    std::vector<unsigned char> mCollision{};
};