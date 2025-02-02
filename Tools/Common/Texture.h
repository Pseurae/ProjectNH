#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string &fpath);
    ~Texture();

    auto GetWidth() const { return mWidth; }
    auto GetHeight() const { return mHeight; }
    void *GetID() const { return (void *)(uintptr_t)mID; }
private:
    int mWidth, mHeight;
    unsigned int mID;
};