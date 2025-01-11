#pragma once

#include <Ethyl/Pointers.h>
#include <Tonic/Graphics/Texture.h>
#include <string>

Ethyl::Shared<Tonic::Graphics::Texture> LoadTexture(const std::string &fname);