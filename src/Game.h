#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
public:
    Game();
    ~Game();

    bool Initialize(const char *windowTitle);
    void Setup();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

private:
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
};

#endif