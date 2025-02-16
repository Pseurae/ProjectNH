#include "Map.h"
#include <Ethyl/Assert.h>

void MapContent::Clear(void)
{
    mEntities.clear();
    mLayers.clear();
}

void MapContent::Load(const toml::table &tbl)
{
}

toml::table MapContent::Save(void)
{
    toml::table mainTbl {
        { "width", mDimensions.x },
        { "height", mDimensions.y }
    };

    toml::array layersArr;
    for (const auto &l : mLayers)
    {
        toml::table layerTbl {
            { "z", l.z }
        };

        toml::array tilesArray;
        for (const auto &tile : l.tiles)
            tilesArray.push_back(toml::table{
                { "x", tile.x },
                { "y", tile.y },
                { "id", tile.id },
                { "col", tile.col }
            });
        
        layerTbl.emplace("tiles", tilesArray);
        layersArr.push_back(layerTbl);
    }

    mainTbl.emplace("layers", layersArr);
    return mainTbl;
}
