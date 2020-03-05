#pragma once
#include "Interfaces/Board.h"
#include "AI/MonteCarloTreeSearchAi.h"
#include <memory>

struct SDL_Renderer;
struct SDL_Window;

class Application
{
public:
    Application();
    void Run();
private:
    bool Initialize();
    void CleanUp();

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_pWindow;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_pRenderer;
    Board* m_pBoard;
    MonteCarloTreeSearchAi m_ai;

};

