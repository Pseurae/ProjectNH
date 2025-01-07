#include "Map.h"
#include <Ethyl/Assert.h>
#include <toml++/toml.hpp>
#include <iostream>
#include "Global.h"
#include <stb_image.h>

auto LoadTileset(const std::string &tilesetName)
{
    int w, h, channels;
    unsigned char *data = stbi_load(tilesetName.c_str(), &w, &h, &channels, 0);
    ETHYL_ASSERT(data, "Error loading image.");
    auto texture = global.gfxDevice->CreateTexture({ data, w, h, channels });
    stbi_image_free(data);
    return Map::Tileset{ texture, w / 16, h / 16 };
}

void Map::Load(const std::string &headerFileName)
{
    auto header = toml::parse_file(headerFileName);

    mMapName = header["name"].value_or<std::string>("");
    mWidth = header["width"].value_or<int>(10);
    mHeight = header["height"].value_or<int>(10);

    toml::array *tilesetArray = header["tilesets"].as_array();
    ETHYL_ASSERT(tilesetArray, "Tileset array does not exist!");

    for (auto &i : *tilesetArray)
    {
        auto tilesetName = i.value<std::string>();
        if (tilesetName) 
            mTilesets.push_back(LoadTileset(tilesetName.value()));
    }

    toml::array *layerArray = header["layers"].as_array();
    ETHYL_ASSERT(layerArray, "Layer array does not exist!");

    for (auto &i : *layerArray)
    {
        toml::table *layerData = i.as_table();
        ETHYL_ASSERT(layerData, "Layer table does not exist!");
        
        Layer layer;
        layer.tilesetId = (*layerData)["tilesetId"].value_or<unsigned char>(0); 

        toml::array *tilemap = (*layerData)["tilemap"].as_array();        
        ETHYL_ASSERT(tilemap, "Tilemap does not exist!");

        for (auto &i : *tilemap)
            layer.tilemap.push_back(i.value_or<unsigned short>(0));
        
        ETHYL_ASSERT(layer.tilemap.size() == mWidth * mHeight, "Tilemap size issue!");
        this->mLayers.push_back(layer);
    }
}

void Map::Render(Tonic::Graphics::SpriteBatch &sb, const glm::vec2 &cameraPos)
{
    for (auto &layer : mLayers)
    {
        auto tilesetTexture = mTilesets[layer.tilesetId].texture;

        for (int x = 0; x < mWidth; ++x)
        for (int y = 0; y < mHeight; ++y)
        {
            int i = layer.tilemap[x + y * mWidth];
            int xtile = i % mTilesets[layer.tilesetId].xtiles;
            int ytile = i / mTilesets[layer.tilesetId].xtiles;

            sb.DrawQuad(glm::vec2{ 16.0 * x, 16.0 * y } - cameraPos, { 16.0, 16.0 },
                tilesetTexture,
                glm::vec4{ 
                    16.0f * xtile,
                    16.0f * ytile,
                    16.0f * (xtile + 1),
                    16.0f * (ytile + 1)
                }
            );
        }
    }
}

bool Map::IsOutOfBounds(const glm::ivec2 &pos)
{
    return (pos.x < 0 || pos.y < 0 || pos.x >= mWidth || pos.y >= mHeight);
}
