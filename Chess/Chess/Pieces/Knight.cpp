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

    int LeftBottomIndex = (m_index - 2) + Chess::kBoardWidth;
    int TopLeftIndex = (m_index - (Chess::kBoardWidth * 2)) - 1;
    int LeftTopIndex = (m_index - 2) - Chess::kBoardWidth;
    int bottomLeftIndex = (m_index + (Chess::kBoardWidth * 2)) - 1;

    //todo refactor into a function
    //TODO isvalidIndex doesnt need to be in gamestate
    if (remainder >= kKightLeftRemainder) 
    {
        // Top Left
        // [X][ ]
        //    [ ]
        if (Chess::IsValidIndex(TopLeftIndex)) 
        {
            Piece* pPiece = pGameState->GetSquare(TopLeftIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(TopLeftIndex);
            }
        }

        // Left Top
        // [X]
        // [ ][ ]
        if (Chess::IsValidIndex(LeftTopIndex))
        {
            Piece* pPiece = pGameState->GetSquare(LeftTopIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(LeftTopIndex);
            }
        }
        // Left Bottom
        // [ ][ ]
        // [X]
        if (Chess::IsValidIndex(LeftBottomIndex))
        {
            Piece* pPiece = pGameState->GetSquare(LeftBottomIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(LeftBottomIndex);
            }
        }

        // Bottom Left
        //    [ ]
        // [X][ ]
        if (Chess::IsValidIndex(bottomLeftIndex))
        {
            Piece* pPiece = pGameState->GetSquare(bottomLeftIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(bottomLeftIndex);
            }
        }
    }

    int RightBottomIndex = (m_index + 2) + Chess::kBoardWidth;
    int TopRightIndex = (m_index - (Chess::kBoardWidth * 2)) + 1;
    int RightTopIndex = (m_index + 2) - Chess::kBoardWidth;
    int bottomRightIndex = (m_index + (Chess::kBoardWidth * 2)) + 1;

    if (remainder <= kKnightRightRemainder)
    {

        // Top Right
        // [ ][X]
        // [ ]
        if (Chess::IsValidIndex(TopRightIndex))
        {
            Piece* pPiece = pGameState->GetSquare(TopRightIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(TopRightIndex);
            }
        }

        // Right Top
        //    [X]
        // [ ][ ]
        if (Chess::IsValidIndex(RightTopIndex))
        {
            Piece* pPiece = pGameState->GetSquare(RightTopIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(RightTopIndex);
            }
        }

        // Right Bottom
        // [ ][ ]
        //    [X]
        if (Chess::IsValidIndex(RightBottomIndex))
        {
            Piece* pPiece = pGameState->GetSquare(RightBottomIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(RightBottomIndex);
            }
        }

        // Bottom Right
        // [ ]
        // [ ][X]
        if (Chess::IsValidIndex(bottomRightIndex))
        {
            Piece* pPiece = pGameState->GetSquare(bottomRightIndex).GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(bottomRightIndex);
            }
        }
    }
    return moves;
}
