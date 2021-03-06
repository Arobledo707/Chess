#include "Rook.h"
#include "../ChessGameState.h"

Rook::Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kRook)
{
}

void Rook::Move(unsigned int move)
{
    SetMoved();
    Piece::Move(move);
}


Moves Rook::GetAvailableMoves(ChessGameState* pGameState)
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
    // if rook isnt on top row then we can move up
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

    // if rook isnt on bottom row then we can move down
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

    return moves;
}
