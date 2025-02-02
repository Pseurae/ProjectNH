#include "Window.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

#include "Log.h"
#include "Application.h"
#include "EventBus.h"
#include "FileDialog.h"

Window::Window(const WindowDesc &desc) :
    mName(desc.name), mWidth(desc.width), mHeight(desc.height)
{
    InitGLFW();
    InitImGui();
    FileDialog::Init(mWindow);
}

Window::~Window()
{
    FileDialog::Quit();
    ShutdownImGui();
    ShutdownGLFW();
}

void Window::InitGLFW()
{
    NH_ASSERT(glfwInit(), "GLFW couldn't be initialized.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);

    float dpiScaleX, dpiScaleY;
    glfwGetWindowContentScale(mWindow, &dpiScaleX, &dpiScaleY);
    mDpiScale = std::max(dpiScaleX, dpiScaleY);

    glfwSetWindowSize(mWindow, mWidth * mDpiScale, mHeight * mDpiScale);

    glfwSetDropCallback(mWindow, [](GLFWwindow *window, int path_count, const char *paths[]) {
        if (path_count <= 0)
            return;

        Events::FileDrag ev;
        for (int i = 0; i < path_count; ++i)
            ev.files.push_back(paths[i]);

        gEventBus.Post<Events::FileDrag>(ev);
    });

    glfwMaximizeWindow(mWindow);
    glfwShowWindow(mWindow);
}

void Window::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    auto &io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.FontGlobalScale *= mDpiScale;

    gEventBus.Post<Events::GuiContextCreated>();

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::ShutdownGLFW()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Window::ShutdownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::Loop(Application &app)
{
    while (!glfwWindowShouldClose(mWindow))
    {
        if (glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED) || 
            !glfwGetWindowAttrib(mWindow, GLFW_VISIBLE))
        {
            glfwWaitEvents();
        }
        else
        {
            glfwPollEvents();
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        gEventBus.Post<Events::Frame>();

        int displayW, displayH;

        ImGui::Render();
        glfwGetFramebufferSize(mWindow, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mWindow);
    }
}
