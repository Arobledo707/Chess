#pragma once
#include "../../Interfaces/Piece.h"
class Knight : public Piece
{
public:
    Knight(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

