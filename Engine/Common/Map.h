#pragma once

#include <list>
#include <unordered_map>
#include <string>
#include <toml++/toml.hpp>
#include <glm/vec2.hpp>

class MapContent final
{
public:
    struct Tile final { unsigned short x, y, id, col; };
    struct Layer final 
    { 
        int z;
        std::list<Tile> tiles;
    };

    struct Entity final
    {
        unsigned short x, y;
        std::string scriptPath;
    };

    auto &GetLayers() { return mLayers; }
    auto GetTilesetNum() const { return mTilesetNum; }
    auto &GetDimensions() { return mDimensions; }

    void Clear(void);
    void Load(const toml::table &tbl);
    toml::table Save(void);

private:
    unsigned short mTilesetNum;
    glm::ivec2 mDimensions;

    std::list<Entity> mEntities;
    std::list<Layer> mLayers;
};