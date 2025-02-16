#include "ToolKit.h"
#include "Panes/Tilesets.h"
#include "Panes/Map.h"
#include <Global.h>
#include <InternalEvents.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

ToolKit::ToolKit()
{
    global.eventBus.Register<Events::Init, &ToolKit::Init>(this);
    global.eventBus.Register<Events::Shutdown, &ToolKit::Shutdown>(this);

    global.eventBus.Register<Events::PreRender, &ToolKit::PreRender>(this);
    global.eventBus.Register<Events::Render, &ToolKit::Render>(this);
    global.eventBus.Register<Events::PostRender, &ToolKit::PostRender>(this);

    mPanes.push_back(Ethyl::CreateUnique<TilesetsPane>());
    mPanes.push_back(Ethyl::CreateUnique<MapPane>());
}

ToolKit::~ToolKit()
{
    global.eventBus.Remove<Events::Init, &ToolKit::Init>(this);
    global.eventBus.Remove<Events::Shutdown, &ToolKit::Shutdown>(this);

    global.eventBus.Remove<Events::PreRender, &ToolKit::PreRender>(this);
    global.eventBus.Remove<Events::Render, &ToolKit::Render>(this);
    global.eventBus.Remove<Events::PostRender, &ToolKit::PostRender>(this);
}

void ToolKit::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.FontGlobalScale *= global.window.GetContentScale();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(global.window.GetNativeHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ToolKit::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ToolKit::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ToolKit::Render()
{
    for (auto &pane : mPanes)
    {
        const auto &windowName = pane->GetWindowName();

        if (pane->GetOpenState())
        {
            ImGui::Begin(windowName.c_str());
            pane->Draw();
            ImGui::End();
        }
    }
}

void ToolKit::PostRender()
{
    ImGui::GetIO().DisplaySize = ImVec2(
        global.window.GetWindowSize().x, 
        global.window.GetWindowSize().y);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
