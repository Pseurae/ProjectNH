#include "Binary.h"
#include <fstream>

std::vector<unsigned char> LoadBinary(const std::string &fpath)
{
    std::ifstream t(fpath, std::ios::binary);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();

    std::vector<unsigned char> contents(size, 0);

    t.seekg(0);
    t.read((char *)contents.data(), size); 

    t.close();

    return contents;
}