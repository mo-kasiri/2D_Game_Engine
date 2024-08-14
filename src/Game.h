#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>

class Game
{

public:
    Game();
    ~Game();

    bool Initialize(const std::string &windowTitle, const unsigned int &width, const unsigned int &height);
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

private:
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    unsigned int m_width;
    unsigned int m_height;
};

#endif