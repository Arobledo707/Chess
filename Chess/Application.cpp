#include "Application.h"
#include "Chess/ChessBoard.h"
#include "Constants/Constants.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
//#include <experimental/filesystem>
Application::Application()
    :m_pWindow(nullptr, SDL_DestroyWindow),
    m_pRenderer(nullptr, SDL_DestroyRenderer),
    m_pBoard(nullptr)
{

}

bool Application::Initialize()
{
    //std::experimental::filesystem::v1::
    if (0 != SDL_Init(SDL_INIT_VIDEO)) 
    {
        return 1;
    }
    m_pWindow.reset(SDL_CreateWindow(kWindowName, 100, 100, kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));
    m_pRenderer.reset(SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));

    if (TTF_Init() != 0) 
    {
        return 1;
    }
    
    m_pBoard = std::make_unique<ChessBoard>();

    return true;

}

void Application::Run()
{
    assert(m_pRenderer.get());
    assert(m_pWindow.get());
    assert(m_pBoard.get());

    m_pBoard->Initialize(m_pRenderer.get());

    bool running = true;
    SDL_Event event;
    double deltaSeconds = 0.0;

    unsigned long long currentTick = SDL_GetPerformanceCounter();
    unsigned long long lastTick = 0;

    m_pBoard->StartGame();

    while (running) 
    {
        lastTick = currentTick;
        currentTick = SDL_GetPerformanceCounter();
        deltaSeconds = ((currentTick - lastTick) / (double)SDL_GetPerformanceCounter());

        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                running = false;

                break;
            case SDL_MOUSEBUTTONDOWN:
                m_pBoard.get()->OnClick();
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(m_pRenderer.get(), 150, 150, 150, 255);
        SDL_RenderClear(m_pRenderer.get());
        m_pBoard.get()->Render(m_pRenderer.get()); 
        
        SDL_RenderPresent(m_pRenderer.get());
    }

    CleanUp();

}

void Application::CleanUp()
{
    TTF_Quit();
    SDL_Quit();
}
