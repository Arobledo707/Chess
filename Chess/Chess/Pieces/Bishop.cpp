#include "Bishop.h"
#include "../ChessGameState.h"
#include "../../Constants/Constants.h"

Bishop::Bishop(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kBishop)
{
}
Moves Bishop::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    Moves moves{};

    int remainder = m_index % Chess::kBoardWidth;

    // right side moves
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
                    moves.push_back(std::pair<int, int>(m_index, currentIndex));
                    break;
                }
            }
            moves.push_back(std::pair<int, int>(m_index, currentIndex));
            currentIndex -= (Chess::kBoardWidth - 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kLeftSideRemainder)
            {
                break;
            }
        }

        // moving right and down
        currentIndex = (m_index + 1) + Chess::kBoardWidth;
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
                    moves.push_back(std::pair<int, int>(m_index, currentIndex));
                    break;
                }
            }
            moves.push_back(std::pair<int, int>(m_index, currentIndex));
            currentIndex += (Chess::kBoardWidth + 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kLeftSideRemainder)
            {
                break;
            }
        }

    }

    //left side moves

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
                    moves.push_back(std::pair<int, int>(m_index, currentIndex));
                    break;
                }
            }
            moves.push_back(std::pair<int, int>(m_index, currentIndex));
            currentIndex -= (Chess::kBoardWidth + 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kRightSideRemainder)
            {
                break;
            }
        }

        // moving left and down
        currentIndex = (m_index - 1) + Chess::kBoardWidth;
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
                    moves.push_back(std::pair<int, int>(m_index, currentIndex));
                    break;
                }
            }
            moves.push_back(std::pair<int, int>(m_index, currentIndex));
            currentIndex += (Chess::kBoardWidth - 1);
            int currentRemainder = currentIndex % Chess::kBoardWidth;
            if (currentRemainder == Chess::kRightSideRemainder)
            {
                break;
            }
        }
    }

    return moves;
}
