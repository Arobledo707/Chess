#include "Queen.h"

Queen::Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Queen::Move()
{
}


std::vector<unsigned int> Queen::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
