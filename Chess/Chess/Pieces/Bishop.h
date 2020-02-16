#pragma once
#include "../../Interfaces/Piece.h"
class Bishop : public Piece
{
public:
    Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual std::vector<unsigned int> GetAvailableMoves(ChessGameState* pGameState) override;
};

