#include "Game.h"

Game::Game()
{
    m_isRunning = false;
    spdlog::info("Game instructor, {}!", "called");
    //  TODO..
}

Game::~Game()
{
    spdlog::info("Game destructor is called");
}

bool Game::Initialize(const char *windowTitle)
{
    // m_WindowWidth = width;
    // m_windowHeight = height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // std::cerr << "Error Initializing SDL!" << std::endl;
        spdlog::error("Error Initializing SDL!: {}", 1);
        return false;
    }

    // Use SDL to query what is the fullscreen max. width and height
    if (SDL_GetNumVideoDisplays() > 0)
    {
        static int display_in_use = 0; /* Only using first display */

        int i, display_mode_count;
        SDL_DisplayMode mode;
        SDL_DisplayMode *modes = (SDL_DisplayMode *)malloc(sizeof(SDL_DisplayMode) * SDL_GetNumDisplayModes(display_in_use));
        Uint32 f;

        SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());

        display_mode_count = SDL_GetNumDisplayModes(display_in_use);

        SDL_Log("SDL_GetNumDisplayModes: %i", display_mode_count);

        for (i = 0; i < display_mode_count; ++i)
        {
            if (SDL_GetDisplayMode(display_in_use, i, &mode) != 0)
            {
                SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
                return 1;
            }
            f = mode.format;
            modes[i] = mode;

            SDL_Log("Mode %i\tbits per pixel %i\t%s\t%i x %i",
                    i, SDL_BITSPERPIXEL(f),
                    SDL_GetPixelFormatName(f),
                    mode.w, mode.h);
        }
        m_windowWidth = modes[0].w;
        m_windowHeight = modes[0].h;

        free(modes);
    }

    m_window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_windowWidth,
        m_windowHeight,
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

    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

    m_isRunning = true;
    return true;
};

void Game::Setup()
{
    m_millisecsPreviousFrame = 0;

    // Initialize game objects
    m_playerPosition = glm::vec2(10, 10);
    m_velocity = glm::vec2(20, 20);
}

void Game::Run()
{
    this->Setup();
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
    // TODO: If we are too fast, waste some time untill we reach the MILISECS_PER_FRAME, lock execution insided while loop
    unsigned int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - m_millisecsPreviousFrame);
    m_deltaTime = (SDL_GetTicks() - m_millisecsPreviousFrame) / 1000.0f;
    m_millisecsPreviousFrame = SDL_GetTicks();
    if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // Updateing game Actors
    m_playerPosition += m_velocity * m_deltaTime;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 25, 21, 21, 255);
    SDL_RenderClear(m_renderer);

    // Draw a PNG texture
    SDL_Surface *surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    // What is the destination rectangle that we want to place our texture
    SDL_Rect dstRect = {
        static_cast<int>(m_playerPosition.x),
        static_cast<int>(m_playerPosition.y),
        32,
        32};
    SDL_RenderCopy(m_renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(m_renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
