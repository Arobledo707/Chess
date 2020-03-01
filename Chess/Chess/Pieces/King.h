#pragma once
#include "../../Interfaces/Piece.h"
class King : public Piece
{
public:
    King(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move(unsigned int move) override;
    virtual Moves GetAvailableMoves(ChessGameState* pGameState) override;

    bool IsInCheck() const { return m_isInCheck; }
    void SetCheck(bool check) { m_isInCheck = check; }
private:
    bool CanCastle(int index, bool leftSide, ChessGameState* pGameState);

private:
    bool m_isInCheck = false;
};

