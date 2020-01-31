#pragma once
#include "../../Interfaces/Piece.h"
class Rook : public Piece
{
    // Inherited via Piece
    virtual void Move() override;
    virtual void Render(SDL_Renderer* pRenderer) override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

