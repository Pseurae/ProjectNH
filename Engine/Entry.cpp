#include "Global.h"
#include "InternalEvents.h"

#include <Tonic/Time.h>

Global global;

void WindowCloseCallback(void)
{
    global.isRunning = false;
}

void WindowKeyCallback(Tonic::Input::Key key, Tonic::Input::Action action, Tonic::Input::KeyMod mods)
{
    global.eventBus.Post<Events::KeyboardInput>(key, action, mods);
}

template<typename... Events>
void SignalEvents(auto&& ...args)
{
    (global.eventBus.Post<Events>(std::forward<decltype(args)>(args)...), ...);
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

    global.gfxDevice = Ethyl::CreateShared<Tonic::Graphics::Device>(global.window);
    global.gfxDevice->SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });

    global.window.SetCloseCallback(WindowCloseCallback);
    global.window.SetKeyCallback(WindowKeyCallback);

    global.startTime = Tonic::Time::Get();
    global.tickRate =  1.0 / global.configuation["internal"]["tickrate"].value_or(60);
    double tickRemainder = 0.0,
        currentTime = global.startTime,
        lastTime = global.startTime;
    
    Game game;
    global.game = &game;
    game.Init();

    SignalEvents<Events::Init>();

    // Maybe move the function calls to the eventbus in the future?
    while (global.isRunning)
    {
        lastTime = currentTime;
        currentTime = Tonic::Time::Get();
        global.deltaTime = currentTime - lastTime;

        tickRemainder += global.deltaTime;

        global.window.PumpEvents();
        game.Update();

        for (; tickRemainder > global.tickRate; tickRemainder -= global.tickRate)
            game.Tick();

        global.gfxDevice->Clear();
        game.Render();
        global.gfxDevice->Present();
    }

    SignalEvents<Events::Quit>();
    game.Shutdown();

    global.gfxDevice.reset();
    global.window.Close();

    return 0;
}

#undef STATE_CALL