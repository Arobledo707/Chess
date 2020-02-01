#pragma once
#include "../../Interfaces/Piece.h"
class Knight : public Piece
{
public:
    Knight(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index);
    // Inherited via Piece
    virtual void Move() override;
    virtual void Render(SDL_Renderer* pRenderer) override;
    virtual std::vector<unsigned int> GetAvailableMoves() override;
};

