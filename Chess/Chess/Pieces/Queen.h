#pragma once
#include "../../Interfaces/Piece.h"
class Queen : public Piece
{
public:
    Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual Moves GetAvailableMoves(ChessGameState* pGameState) override;
};

