#pragma once

#include <string>
#include "Window.h"

struct Application
{
    virtual ~Application() = default;
    virtual WindowDesc GetWindowDesc() = 0;
};