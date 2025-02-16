#include <Entry.h>
#include "Game.h"

int main(int argc, char *argv[])
{
    try { EngineMain<Game>(); } 
    catch (std::runtime_error &err) { std::cout << err.what() << std::endl; }
    return 0;
}