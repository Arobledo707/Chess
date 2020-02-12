#pragma once
#include "Interfaces/Board.h"
#include <memory>

struct SDL_Renderer;
struct SDL_Window;

class Application
{
public:
    Application();
    bool Initialize();
    void Run();
private:
    void CleanUp();

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_pWindow;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_pRenderer;
    std::unique_ptr<Board> m_pBoard;

};

