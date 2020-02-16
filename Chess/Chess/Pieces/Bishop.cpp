#include "Bishop.h"

Bishop::Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Bishop::Move()
{
}


std::vector<unsigned int> Bishop::GetAvailableMoves(ChessGameState* pGameState)
{
    return std::vector<unsigned int>();
}
