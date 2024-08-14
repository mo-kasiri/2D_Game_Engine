#include "Game.h"

Game::Game()
{
    m_isRunning = false;
    std::cout << "Game construction called!" << std::endl;
    // TODO..
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}

bool Game::Initialize(const std::string &windowTitle, const unsigned int &width, const unsigned int &height)
{
    m_width = width;
    m_height = height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error Initializing SDL!" << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS);

    if (!m_window)
    {
        std::cerr << "Error creating SDL window!" << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(this->m_window, -1, 0);
    if (!m_renderer)
    {
        std::cerr << "Error creating SDL renderer!" << std::endl;
        return false;
    }
    m_isRunning = true;
    return true;
};

void Game::Run()
{
    while (m_isRunning)
    {
        this->ProcessInput();
        this->Update();
        this->Render();
    }
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                m_isRunning = false;
            }
            break;
        }
    }
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::Destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
