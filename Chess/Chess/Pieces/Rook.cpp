#include "Rook.h"

Rook::Rook(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index), m_hasMoved(false)
{
}

void Rook::Move()
{
}

void Rook::Render(SDL_Renderer* pRenderer)
{
}

std::vector<unsigned int> Rook::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
