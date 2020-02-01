#include "Knight.h"

Knight::Knight(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Knight::Move()
{
}

void Knight::Render(SDL_Renderer* pRenderer)
{
}

std::vector<unsigned int> Knight::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
