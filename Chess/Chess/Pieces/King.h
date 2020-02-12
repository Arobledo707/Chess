#pragma once
#include "../../Interfaces/Piece.h"
class King : public Piece
{
public:
    King(SDL_Texture* pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
private:
    bool m_hasMoved = false;
};

