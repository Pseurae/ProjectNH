#include "Global.h"
#include "InternalEvents.h"

#include <Tonic/Time.h>

Global global;

void WindowCloseCallback(void)
{
    global.isRunning = false;
}

int main(int argc, char *argv[])
{
    global.configuation = toml::parse_file("Assets/settings.toml");

    auto windowName = global.configuation["window"]["name"].value_or("ProjectNH");
    auto windowWidth = global.configuation["window"]["width"].value_or(800);
    auto windowHeight = global.configuation["window"]["height"].value_or(600);

    ETHYL_ASSERT(
        global.window.Create({ windowName, windowWidth, windowHeight}),
        "Window could not be created."
    );

    global.window.SetCloseCallback(WindowCloseCallback);

    global.startTime = Tonic::Time::Get();

    double tickRemainder = 0.0,
        currentTime = global.startTime,
        lastTime = global.startTime;

    global.tickRate =  1.0 / global.configuation["internal"]["tickrate"].value_or(60);

    global.eventBus.Post<Events::Init>();

    while (global.isRunning)
    {
        lastTime = currentTime;
        currentTime = Tonic::Time::Get();
        global.deltaTime = currentTime - lastTime;

        tickRemainder += global.deltaTime;

        global.eventBus.Post<Events::PreUpdate>();
        if (global.state) global.state->Update();
        global.eventBus.Post<Events::PostUpdate>();

        global.window.PumpEvents();

        for (; tickRemainder > global.tickRate; tickRemainder -= global.tickRate)
        {
            global.eventBus.Post<Events::PreTick>();
            if (global.state) global.state->Tick();
            global.eventBus.Post<Events::PostTick>();
        }

        global.eventBus.Post<Events::PreRender>();
        if (global.state) global.state->Render();
        global.eventBus.Post<Events::PostRender>();
    }

    return 0;
}