#pragma once

#include <vector>
#include <string>
#include <Tonic/Graphics/Texture.h>
#include <Tonic/Graphics/SpriteBatch.h>
#include <Ethyl/Pointers.h>

class Map final
{
public:
    struct Layer
    {
        unsigned char tilesetId;
        std::vector<unsigned short> tilemap;
    };

    struct Tileset
    {
        Ethyl::Shared<Tonic::Graphics::Texture> texture;
        int xtiles, ytiles;
    };

    Map() = default;
    ~Map() = default;

    void Load(const std::string &headerFileName);
    void Render(Tonic::Graphics::SpriteBatch &sb, const glm::vec2 &cameraPos);

    bool IsOutOfBounds(const glm::ivec2 &pos);
private:
    std::string mMapName;
    unsigned char mWidth, mHeight;
    std::vector<Layer> mLayers;
    std::vector<Tileset> mTilesets;
};