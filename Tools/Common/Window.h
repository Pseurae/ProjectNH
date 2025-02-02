#pragma once

#include <string>

class Application;
struct GLFWwindow;

struct WindowDesc
{
    std::string name;
    int width, height;
};

class Window final
{
public:
    Window(const WindowDesc &desc);
    ~Window();

    void InitGLFW();
    void InitImGui();
    
    void ShutdownGLFW();
    void ShutdownImGui();

    void Loop(Application &app);

    GLFWwindow *GetNativeWindow() const { return mWindow; }

private:
    GLFWwindow *mWindow;
    std::string mName;
    int mWidth, mHeight;
    float mDpiScale;
};