#include "Window.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

#include "Assert.h"

Window::Window(const std::string &name, int width, int height) :
    mName(name), mWidth(width), mHeight(height)
{
    InitGLFW();
    InitImGui();
}

Window::~Window()
{
    ShutdownImGui();
    ShutdownGLFW();
}

void Window::InitGLFW()
{
    NH_ASSERT(glfwInit(), "GLFW couldn't be initialized.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);
}

void Window::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

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

void Window::FrameStart()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::Frame()
{
}

void Window::FrameEnd()
{
    int displayW, displayH;

    ImGui::Render();
    glfwGetFramebufferSize(mWindow, &displayW, &displayH);
    glViewport(0, 0, displayW, displayH);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(mWindow);
}

void Window::Run()
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

        FrameStart();
        Frame();
        FrameEnd();
    }
}
