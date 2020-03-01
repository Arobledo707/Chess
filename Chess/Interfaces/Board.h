#pragma once
#include <SDL.h>
#include <memory>
#include "../Constants/Constants.h"
struct SDL_Renderer;
class Board
{
public:
    virtual ~Board() = default;

    virtual void Initialize(SDL_Renderer* pRenderer) = 0;
    virtual int StartGame() = 0;
    virtual const int GetCurrentPlayer() const = 0;
    virtual const Moves GetAvailableMoves() = 0;
    virtual const bool OnClick() = 0;
    virtual void MakeMove(Move move) = 0;
    virtual int CheckForGameEnd() const = 0;
    virtual int PrintGameEnd() = 0;
    virtual const int GetPlayerColor() const = 0;
    virtual Board* CloneSelf() const = 0;
    virtual void AlternateTurns() = 0;

    virtual void Render(SDL_Renderer* pRenderer) = 0;
};

