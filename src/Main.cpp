#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char *argv[])
{
    Game game;
    game.Initialize("2D Game Engine", 800, 600);
    game.Run();
    game.Destroy();
    return 0;
}
