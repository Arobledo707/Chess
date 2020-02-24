#include "Bishop.h"
#include "../ChessGameState.h"

Bishop::Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kBishop)
{
}

void Bishop::Move(unsigned int move)
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
        int currentIndex = (m_index - 1) - Chess::kBoardWidth;
        while (Chess::IsValidIndex(currentIndex))
        {

        }



        // moving left and down

    }

    if (remainder != Chess::kRightSideRemainder)
    {

    }

    return moves;
}
