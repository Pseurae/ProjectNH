#pragma once

#include "ImGui/Pane.h"

class MapPane final : public Pane
{
public:
    virtual void Draw() override final;
    virtual const std::string GetWindowName() override final { return "Maps"; }
};