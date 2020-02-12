#include "Pawn.h"


Pawn::Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Pawn::Move()
{
}


std::vector<unsigned int> Pawn::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
