#include "MapEditor.h"
#include "EventBus.h"
#include "Context.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include <FileDialog.h>

Context gContext;

Application *CreateApplication(void)
{
    return new MapEditor();
}

MapEditor::MapEditor()
{
    gEventBus.Register<Events::Frame, &MapEditor::Frame>(this);
}

MapEditor::~MapEditor()
{
    gEventBus.Remove<Events::Frame, &MapEditor::Frame>(this);
}

WindowDesc MapEditor::GetWindowDesc()
{
    return WindowDesc{"MapEditor", 800, 600};
}

void MapEditor::Frame()
{
    ImGuiWindowFlags backgroundWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;

    MainMenuBar();

    switch (gContext.mode)
    {
    case Mode::Tilemap:
        TilemapMode();
        break;
    }
}

void MapEditor::MainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode"))
        {
            if (ImGui::MenuItem("Tilemap", nullptr, gContext.mode == Mode::Tilemap))
                gContext.mode = Mode::Tilemap;
            if (ImGui::MenuItem("Sprites", nullptr, gContext.mode == Mode::Sprites))
                gContext.mode = Mode::Sprites;
            if (ImGui::MenuItem("Entity", nullptr, gContext.mode == Mode::Entity))
                gContext.mode = Mode::Entity;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void MapEditor::TilemapMode()
{
    ImGui::SetNextWindowSize(ImVec2(500.0, 800.0));

    ImGui::Begin("Tileset Viewer");
    if (ImGui::Button("Load"))
    {
        std::string res;
        if (FileDialog::Open(FileDialog::Mode::Open, { { "Tileset Image", "png" } }, res))
            gContext.map.GetTileset().Load(res);
    }

    if (ImGui::BeginChild("###Tileset"))
    {
        ImGui::EndChild();
    }
    ImGui::End();
}
