#pragma once
#include "../../Interfaces/Piece.h"
#include "../../Constants/ChessConstants.h"
class Pawn : public Piece
{
public:
    Pawn(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual void Render(SDL_Renderer* pRenderer) override;

    // Inherited via Piece
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

