#include "Window.h"
#include "Application.h"

extern Application *CreateApplication(void);

int main(int argc, char *argv[])
{
    auto *app = CreateApplication();
    Window window(app->GetWindowDesc());
    window.Loop(*app);
    delete app;
    return 0;
}