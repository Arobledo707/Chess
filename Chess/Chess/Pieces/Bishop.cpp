#include "Bishop.h"
#include "../ChessGameState.h"

Bishop::Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Bishop::Move()
{
}


std::vector<unsigned int> Bishop::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    std::vector<unsigned int> moves{};

    int remainder = m_index % Chess::kBoardWidth;


    if (remainder != Chess::kLeftSideRemainder) 
    {
        // moving left and up

        // moving left and down

    }

    if (remainder != Chess::kRightSideRemainder)
    {

    }

    return moves;
}
