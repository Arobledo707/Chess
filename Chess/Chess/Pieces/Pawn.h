#pragma once
#include "../../Interfaces/Piece.h"
#include "../../Constants/ChessConstants.h"
class Pawn : public Piece
{
public:
    Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move(unsigned int move) override;
    virtual std::vector<unsigned int> GetAvailableMoves(ChessGameState* pGameState) override;
private:
    bool m_hasMoved = false;
    int m_moveOffset = 1;
};

