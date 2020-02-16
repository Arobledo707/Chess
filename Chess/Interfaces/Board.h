#pragma once
#include <SDL.h>
#include <memory>
struct SDL_Renderer;
class Board
{
public:
    virtual ~Board() = default;

    virtual void Initialize(SDL_Renderer* pRenderer) = 0;
    virtual void StartGame() = 0;
    virtual const int GetCurrentPlayer() const = 0;
    virtual const int GetAvailableMoves() const = 0;
    virtual const bool GetClick() = 0;
    virtual void MakeMove() = 0;
    virtual int CheckForGameEnd() const = 0;
    virtual int PrintGameEnd() = 0;

    virtual void Render(SDL_Renderer* pRenderer) = 0;
};

