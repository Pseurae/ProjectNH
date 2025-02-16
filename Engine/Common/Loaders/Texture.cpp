#include "Loaders/Texture.h"
#include <Ethyl/Assert.h>
#include <Global.h>
#include <stb_image.h>

Ethyl::Shared<Tonic::Graphics::Texture> LoadTexture(const std::string &fname)
{
    int w, h, channels;
    unsigned char *data = stbi_load(fname.c_str(), &w, &h, &channels, 0);
    ETHYL_ASSERT(data, "Error loading image.");
    auto ret = global.gfxDevice->CreateTexture({ data, w, h, channels });
    stbi_image_free(data);

    return ret;
}