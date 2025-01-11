#include "Tileset.h"
#include "Loaders/Binary.h"
#include "Loaders/Texture.h"
#include <Ethyl/Assert.h>
#include <unordered_map>
#include <filesystem>
#include <toml++/toml.hpp>

static std::unordered_map<std::string, TilesetDesc> sTilesetDescs;

void LoadTilesetDescs(const std::string &fpath)
{
    for (const auto &e : std::filesystem::directory_iterator(fpath))
    {
        auto name = std::filesystem::relative(e.path(), fpath).string();
        TilesetDesc desc;

        desc.tiles = (e.path() / "tiles.png").string();
        desc.collision = (e.path() / "collision.bin").string();

        sTilesetDescs.insert({ name, desc });
    }
}

void Tileset::Load(const std::string &name)
{
    ETHYL_ASSERT(sTilesetDescs.count(name) > 0, "No tileset found.");
    mName = name;
    Load(sTilesetDescs[name]);
}

void Tileset::Load(const TilesetDesc &desc)
{
    mTexture = LoadTexture(desc.tiles);
    mCollision = LoadBinary(desc.collision);
    
    glm::ivec2 textureSize = mTexture->GetSize();
    mXTiles = textureSize.x / 16;
    mYTiles = textureSize.y / 16;

    ETHYL_ASSERT(mCollision.size() == mXTiles * mYTiles, "Collision element count mismatch!");
    ETHYL_ASSERT(mTexture->GetSize() == (glm::vec2{ mXTiles * 16.0f, mYTiles * 16.0f }),
        "Tile count mismatch!");
}