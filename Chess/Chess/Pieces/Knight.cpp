#include "Knight.h"
#include "../ChessGameState.h"

Knight::Knight(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kKnight)
{
}


std::vector<unsigned int> Knight::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    std::vector<unsigned int> moves;
    int remainder = m_index % Chess::kBoardWidth;
    const unsigned int kKightLeftRemainder = 1;
    const unsigned int kKnightRightRemainder = 6;

    int leftBottomIndex = (m_index - 2) + Chess::kBoardWidth;
    int topLeftIndex = (m_index - (Chess::kBoardWidth * 2)) - 1;
    int leftTopIndex = (m_index - 2) - Chess::kBoardWidth;
    int bottomLeftIndex = (m_index + (Chess::kBoardWidth * 2)) - 1;

    if (remainder >= kKightLeftRemainder) 
    {
        // Top Left
        // [X][ ]
        //    [ ]
        if (Chess::IsValidIndex(topLeftIndex)) 
        {
            AddMoveIfValid(topLeftIndex, moves, pGameState);
        }

        // Bottom Left
        //    [ ]
        // [X][ ]
        if (Chess::IsValidIndex(bottomLeftIndex))
        {
            AddMoveIfValid(bottomLeftIndex, moves, pGameState);
        }
    }

    if (remainder >= kKightLeftRemainder + kKightLeftRemainder) 
    {
        // Left Top
        // [X]
        // [ ][ ]
        if (Chess::IsValidIndex(leftTopIndex))
        {
            AddMoveIfValid(leftTopIndex, moves, pGameState);
        }
        // Left Bottom
        // [ ][ ]
        // [X]
        if (Chess::IsValidIndex(leftBottomIndex))
        {
            AddMoveIfValid(leftBottomIndex, moves, pGameState);
        }
    }

    int rightBottomIndex = (m_index + 2) + Chess::kBoardWidth;
    int topRightIndex = (m_index - (Chess::kBoardWidth * 2)) + 1;
    int rightTopIndex = (m_index + 2) - Chess::kBoardWidth;
    int bottomRightIndex = (m_index + (Chess::kBoardWidth * 2)) + 1;

    if (remainder <= kKnightRightRemainder)
    {
        // Top Right
        // [ ][X]
        // [ ]
        if (Chess::IsValidIndex(topRightIndex))
        {
            AddMoveIfValid(topRightIndex, moves, pGameState);
        }

        // Bottom Right
        // [ ]
        // [ ][X]
        if (Chess::IsValidIndex(bottomRightIndex))
        {
            AddMoveIfValid(bottomRightIndex, moves, pGameState);
        }
    }

    if (remainder <= kKnightRightRemainder - kKightLeftRemainder) 
    {
        // Right Top
        //    [X]
        // [ ][ ]
        if (Chess::IsValidIndex(rightTopIndex))
        {
            AddMoveIfValid(rightTopIndex, moves, pGameState);
        }

        // Right Bottom
        // [ ][ ]
        //    [X]
        if (Chess::IsValidIndex(rightBottomIndex))
        {
            AddMoveIfValid(rightBottomIndex, moves, pGameState);
        }
    }
    return moves;
}
