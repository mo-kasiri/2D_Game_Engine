#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

const unsigned int MAX_FPS = 120;
const unsigned int MILLISECONDS_PER_FRAME = 1000 / MAX_FPS;

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

    glm::vec2 m_playerPosition;
    glm::vec2 m_velocity;

    unsigned int m_millisecsPreviousFrame;
    float m_deltaTime;
};

#endif