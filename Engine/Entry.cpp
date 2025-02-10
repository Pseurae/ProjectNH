#include "Global.h"
#include "InternalEvents.h"
#include "Game.h"
#include "Tool.h"
#include <iostream>
#include <Tonic/Time.h>

Global global;

template<typename... Events>
static void SignalEvents(auto&& ...args)
{
    (global.eventBus.Post<Events>(std::forward<decltype(args)>(args)...), ...);
}

template<typename T>
void EngineMain(void)
{
    T *instance = new T();

    global.configuation = toml::parse_file("Assets/settings.toml");

    auto windowName = global.configuation["window"]["name"].value_or("Untitled");
    auto windowWidth = global.configuation["window"]["width"].value_or(800);
    auto windowHeight = global.configuation["window"]["height"].value_or(600);

    ETHYL_ASSERT(
        global.window.Create({ windowName, windowWidth, windowHeight}),
        "Window could not be created."
    );

    global.gfxDevice = Ethyl::CreateShared<Tonic::Graphics::Device>(global.window);
    global.gfxDevice->SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });

    global.window.SetCloseCallback(+[]() {
        global.isRunning = false;
    });
    global.window.SetKeyCallback(+[](Tonic::Key key, Tonic::Action action, Tonic::KeyMod mods) {
        global.eventBus.Post<Events::KeyboardInput>(key, action, mods);
    });

    global.startTime = Tonic::Time::Get();
    global.tickRate =  1.0 / global.configuation["internal"]["tickrate"].value_or(60);
    double tickRemainder = 0.0,
        currentTime = global.startTime,
        lastTime = global.startTime;

    SignalEvents<Events::Init>();

    while (global.isRunning)
    {
        lastTime = currentTime;
        currentTime = Tonic::Time::Get();
        global.deltaTime = currentTime - lastTime;

        tickRemainder += global.deltaTime;

        global.window.PumpEvents();
        SignalEvents<Events::PreUpdate, Events::Update, Events::PostUpdate>();

        for (; tickRemainder > global.tickRate; tickRemainder -= global.tickRate)
            SignalEvents<Events::PreTick, Events::Tick, Events::PostTick>();

        global.gfxDevice->Clear();
        SignalEvents<Events::PreRender, Events::Render, Events::PostRender>();
        global.gfxDevice->Present();
    }

    SignalEvents<Events::Shutdown>();

    delete instance;

    global.gfxDevice.reset();
    global.window.Close();
}

int main(int argc, char *argv[])
{
    try { 
#if not defined(NH_EDITOR)
        EngineMain<Game>();
#else
        EngineMain<Tool>();
#endif
    } 
    catch (std::runtime_error &err) { std::cout << err.what() << std::endl; }
    return 0;
}