#include "Rook.h"

Rook::Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index), m_hasMoved(false)
{
}

void Rook::Move()
{
}


std::vector<unsigned int> Rook::GetAvailableMoves(ChessGameState* pGameState)
{
    return std::vector<unsigned int>();
}
