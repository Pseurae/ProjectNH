#include <Entry.h>
#include "ToolKit.h"

int main(int argc, char *argv[])
{
    try { EngineMain<ToolKit>(); } 
    catch (std::runtime_error &err) { std::cout << err.what() << std::endl; }
    return 0;
}