#pragma once

#include <Ethyl/Pointers.h>
#include <vector>
#include "ImGui/Pane.h"

class ToolKit final 
{
public:
    ToolKit();
    ~ToolKit();

    void Init();
    void Shutdown();

    void PreRender();
    void Render();
    void PostRender();
private:
    std::vector<Ethyl::Unique<Pane>> mPanes;
};