#pragma once
#include "../../Interfaces/Piece.h"
#include "../../Constants/ChessConstants.h"
class Pawn : public Piece
{
public:
    Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

