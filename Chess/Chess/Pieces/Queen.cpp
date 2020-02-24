#include "Queen.h"

Queen::Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kQueen)
{
}

void Queen::Move(unsigned int move)
{
}


std::vector<unsigned int> Queen::GetAvailableMoves(ChessGameState* pGameState)
{
    return std::vector<unsigned int>();
}
