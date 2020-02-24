#include "Bishop.h"
#include "../ChessGameState.h"

Bishop::Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kBishop)
{
}

std::vector<unsigned int> Bishop::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    std::vector<unsigned int> moves{};

    int remainder = m_index % Chess::kBoardWidth;


    if (remainder != Chess::kRightSideRemainder)
    {
        // moving right and up
        int currentIndex = (m_index + 1) - Chess::kBoardWidth;
        while (Chess::IsValidIndex(currentIndex))
        {
            Piece* pPiece = pGameState->GetSquare(currentIndex).GetPiece();
            if (pPiece)
            {
                if (pPiece->GetColor() == GetColor())
                {
                    break;
                }
                else
                {
                    moves.push_back(currentIndex);
                    break;
                }
            }
            moves.push_back(currentIndex);
            currentIndex -= (Chess::kBoardWidth - 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kLeftSideRemainder)
            {
                break;
            }
        }


        // moving left and down

    }

    // moving left and up
    if (remainder != Chess::kLeftSideRemainder)
    {
        int currentIndex = (m_index - 1) - Chess::kBoardWidth;
        while (Chess::IsValidIndex(currentIndex))
        {
            Piece* pPiece = pGameState->GetSquare(currentIndex).GetPiece();
            if (pPiece)
            {
                if (pPiece->GetColor() == GetColor())
                {
                    break;
                }
                else
                {
                    moves.push_back(currentIndex);
                    break;
                }
            }
            moves.push_back(currentIndex);
            currentIndex -= (Chess::kBoardWidth + 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kRightSideRemainder)
            {
                break;
            }
        }
    }

    return moves;
}
