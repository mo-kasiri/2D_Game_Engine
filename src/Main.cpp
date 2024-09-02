#include <iostream>
#include <SDL2/SDL.h>
#include "Game/Game.h"

int main(int argc, char *argv[])
{
    Game game;
    game.Initialize("2D Game Engine");
    game.Run(); // While loop
    game.Destroy();
    return 0;
}
