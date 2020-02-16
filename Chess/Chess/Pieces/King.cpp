#include "King.h"

King::King(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void King::Move()
{
}


std::vector<unsigned int> King::GetAvailableMoves(ChessGameState* pGameState)
{
    return std::vector<unsigned int>();
}
