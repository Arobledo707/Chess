#include "Rook.h"
#include "../ChessGameState.h"

Rook::Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index), m_hasMoved(false)
{
}

void Rook::Move()
{
}


std::vector<unsigned int> Rook::GetAvailableMoves(ChessGameState* pGameState)
{
    std::vector<unsigned int> moves;

    //horizontal moves
    int remainder = m_index % Chess::kBoardWidth;
    // if the remainder isn't 0 then we can move right
    if (remainder != Chess::kLeftSideRemainder)
    {

    }

    // if the remainder isn't 7 then we can move right
    if (remainder != Chess::kRightSideRemainder)
    {

    }

    //vertical moves
    // if rook isnt on top row then we can move up
    if (!(m_index < Chess::kBoardWidth))
    {

    }

    if ((m_index > ((Chess::kBoardWidth * Chess::kBoardWidth)-1) - Chess::kBoardWidth))
    {

    }


    return moves;
}
