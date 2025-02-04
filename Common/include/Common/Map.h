#pragma once

#include <vector>
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
        std::string name;
        int z;
        std::vector<Tile> tiles;
    };

    auto &GetLayers() { return mLayers; }
    const auto &GetDimensions() { return mDimensions; }

    void Load(const toml::table &tbl);
    toml::table Save(void);

private:
    std::string mName;
    glm::ivec2 mDimensions;
    std::vector<Layer> mLayers;
};