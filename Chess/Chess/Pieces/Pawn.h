#pragma once
#include "../../Interfaces/Piece.h"
#include "../../Constants/ChessConstants.h"
class Pawn : public Piece
{
public:
    Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move(unsigned int move) override;
    virtual Moves GetAvailableMoves(ChessGameState* pGameState) override;
private:
    int m_moveOffset = 1;
};

