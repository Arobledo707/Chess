#include "Knight.h"

Knight::Knight(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Knight::Move()
{
}

std::vector<unsigned int> Knight::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
