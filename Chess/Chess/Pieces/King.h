#pragma once
#include "../../Interfaces/Piece.h"
class King :
    public Piece
{
public:
    // Inherited via Piece
    virtual void Move() override;
    virtual void Render(SDL_Renderer* pRenderer) override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
private:
    bool m_hasMoved = false;
};

