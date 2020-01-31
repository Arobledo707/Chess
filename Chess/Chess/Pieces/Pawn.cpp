#include "Pawn.h"


Pawn::Pawn(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Pawn::Move()
{
}

void Pawn::Render(SDL_Renderer* pRenderer)
{
}
