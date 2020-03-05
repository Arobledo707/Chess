#include "Queen.h"

#include "../ChessGameState.h"

Queen::Queen(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kQueen)
{
}

// TODO refactor and have it take function from called horizontal,vertical, diagonal
// rook and bishop will use that too
// for now i copy and pasted :((((

Moves Queen::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    Moves moves{};

    //horizontal moves
    // if the remainder isnt 0 then we can move left
    int remainder = m_index % Chess::kBoardWidth;
    if (remainder != Chess::kLeftSideRemainder)
    {
        for (int i = 1; i <= remainder; ++i)
        {
            int currentIndex = m_index - i;
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
        }
    }

    // if the remainder isn't 7 then we can move right
    if (remainder != Chess::kRightSideRemainder)
    {
        for (int i = 1; i < (Chess::kBoardWidth) - (remainder); ++i)
        {
            int currentIndex = m_index + i;
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
        }
    }

    //vertical moves
    // if queen isnt on top row then we can move up
    if (m_index > Chess::kBoardWidth - 1)
    {
        int currentIndex = m_index - Chess::kBoardWidth;
        while (true)
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
            if (currentIndex < Chess::kBoardWidth)
            {
                break;
            }
            currentIndex -= Chess::kBoardWidth;
        }
    }

    // if queen isnt on bottom row then we can move down
    if ((m_index < ((Chess::kBoardSize) - 1) - Chess::kBoardWidth))
    {
        int currentIndex = m_index + Chess::kBoardWidth;
        while (true)
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
            moves.push_back(std::pair<int, int>((int)GetColor(), currentIndex));
            if (currentIndex > (Chess::kBoardSize - 1) - Chess::kBoardWidth)
            {
                break;
            }
            currentIndex += Chess::kBoardWidth;
        }
    }

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
