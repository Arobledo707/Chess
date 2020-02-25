#pragma once
#include "../../Interfaces/Piece.h"
class Rook : public Piece
{
public:
    Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move(unsigned int move) override;
    virtual std::vector<unsigned int> GetAvailableMoves(ChessGameState* pGameState) override;
};

