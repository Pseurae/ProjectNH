#include "Tool.h"
#include "Global.h"
#include "InternalEvents.h"

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui.h>

Tool::Tool()
{
    global.eventBus.Register<Events::Init, &Tool::Init>(this);
    global.eventBus.Register<Events::Shutdown, &Tool::Shutdown>(this);

    global.eventBus.Register<Events::PreRender, &Tool::PreRender>(this);
    global.eventBus.Register<Events::Render, &Tool::Render>(this);
    global.eventBus.Register<Events::PostRender, &Tool::PostRender>(this);
}

Tool::~Tool()
{
    global.eventBus.Remove<Events::Init, &Tool::Init>(this);
    global.eventBus.Remove<Events::Shutdown, &Tool::Shutdown>(this);

    global.eventBus.Remove<Events::PreRender, &Tool::PreRender>(this);
    global.eventBus.Remove<Events::Render, &Tool::Render>(this);
    global.eventBus.Remove<Events::PostRender, &Tool::PostRender>(this);
}

void Tool::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.FontGlobalScale *= global.window.GetContentScale();

    ImGui_ImplGlfw_InitForOpenGL(global.window.GetNativeHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Tool::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Tool::PreRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Tool::Render()
{
    ImGui::Begin("Test");
    ImGui::End();
}

void Tool::PostRender()
{
    ImGui::GetIO().DisplaySize = ImVec2(
        global.window.GetWindowSize().x, 
        global.window.GetWindowSize().y);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
