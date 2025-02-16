#pragma once

#include "ImGui/Pane.h"

class TilesetsPane final : public Pane
{
public:
    virtual void Draw() override final;
    virtual const std::string GetWindowName() override final { return "Tilesets"; }
};