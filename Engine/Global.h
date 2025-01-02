#include <Tonic/Window.h>
#include <Tonic/Graphics/Device.h>
#include <Tonic/Utilities/EventBus.h>
#include <toml++/toml.hpp>
#include "State.h"

struct Global
{
    Tonic::Window window;
    Tonic::EventBus eventBus;
    Ethyl::Shared<Tonic::Graphics::Device> gfxDevice;
    toml::table configuation;
    bool isRunning = true;
    State *state;

    double startTime = 0.0;
    double deltaTime = 0.0;
    double tickRate = 0.0;
};

extern Global global;