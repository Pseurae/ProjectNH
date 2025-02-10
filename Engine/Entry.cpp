#include "Global.h"
#include "InternalEvents.h"
#include <iostream>
#include <Tonic/Time.h>

Global global;

template<typename... Events>
static void SignalEvents(auto&& ...args)
{
    (global.eventBus.Post<Events>(std::forward<decltype(args)>(args)...), ...);
}

int main(int argc, char *argv[])
{
    try {
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

		// IMGUI_CHECKVERSION();
		// ImGui::CreateContext();
        // ImGui::StyleColorsDark();
        // ImGuiIO& io = ImGui::GetIO();
        // io.IniFilename = nullptr;
        // io.FontGlobalScale *= global.window.GetContentScale();

        // ImGui_ImplGlfw_InitForOpenGL(global.window.GetNativeHandle(), true);
		// ImGui_ImplOpenGL3_Init("#version 330");

        // Game game;

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

            // ImGui_ImplOpenGL3_NewFrame();
            // ImGui_ImplGlfw_NewFrame();
            // ImGui::NewFrame();

            // io.DisplaySize = ImVec2(
            //     global.window.GetWindowSize().x, 
            //     global.window.GetWindowSize().y);
            // ImGui::Render();

            global.gfxDevice->Clear();
            SignalEvents<Events::PreRender, Events::Render, Events::PostRender>();
            // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            global.gfxDevice->Present();
        }

        SignalEvents<Events::Shutdown>();

		// ImGui_ImplOpenGL3_Shutdown();
		// ImGui_ImplGlfw_Shutdown();
		// ImGui::DestroyContext();

        global.gfxDevice.reset();
        global.window.Close();
    } 
    catch (std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
    }

    return 0;
}

#undef STATE_CALL