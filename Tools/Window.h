#pragma once

#include <string>

struct GLFWwindow;

class Window final
{
public:
    Window(const std::string &name, int width, int height);
    ~Window();

    void InitGLFW();
    void InitImGui();
    
    void ShutdownGLFW();
    void ShutdownImGui();

    void FrameStart();
    void Frame();
    void FrameEnd();

    void Run();
private:
    GLFWwindow *mWindow;
    std::string mName;
    int mWidth, mHeight;
};