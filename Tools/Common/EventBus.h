#pragma once

#include <Tonic/Utilities/EventBus.h>
#include <vector>
#include <string>

namespace Events
{
struct FileDrag
{
    std::vector<std::string> files;
};

struct GuiContextCreated {};
struct Frame {};
}

extern Tonic::EventBus gEventBus;