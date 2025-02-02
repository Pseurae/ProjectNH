#include "Tileset.h"

void Tileset::Load(const std::string &fname)
{
    mTilesetTexture = std::make_shared<Texture>(fname);
    mWidth = mTilesetTexture->GetWidth() / 16;
    mHeight = mTilesetTexture->GetHeight() / 16;
    mPath = fname;
}

void Tileset::Save(const std::string &fname)
{
}
