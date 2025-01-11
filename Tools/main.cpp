#include "Window.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[])
{
    Window window("Test", 800, 600);
    window.Run();
    return 0;
}