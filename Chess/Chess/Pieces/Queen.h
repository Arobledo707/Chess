#pragma once
#include "../../Interfaces/Piece.h"
class Queen : public Piece
{
public:
    Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

