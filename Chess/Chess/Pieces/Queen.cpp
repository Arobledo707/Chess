#include "Queen.h"

Queen::Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kQueen)
{
}


Moves Queen::GetAvailableMoves(ChessGameState* pGameState)
{
    return Moves();
}
