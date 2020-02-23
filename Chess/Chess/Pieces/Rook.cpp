#include "Rook.h"
#include "../ChessGameState.h"

Rook::Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index), m_hasMoved(false)
{
}

void Rook::Move(unsigned int move)
{
}


std::vector<unsigned int> Rook::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    std::vector<unsigned int> moves{};

    //horizontal moves
    int remainder = m_index % Chess::kBoardWidth;
    // if the remainder isn't 0 then we can move left
    if (remainder != Chess::kLeftSideRemainder)
    {
        unsigned int currentIndex = m_index -= 1;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare) 
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor()) 
            {
                moves.push_back(currentIndex);
            }

            currentIndex -= 1;
            int checkRemainder = currentIndex % Chess::kBoardWidth;
            if (currentIndex != Chess::kLeftSideRemainder)
            {
                pSquare = &pGameState->GetSquare(currentIndex);
            }
            else 
            {
                pSquare = nullptr;
            }
        }

    }

    // if the remainder isn't 7 then we can move right
    if (remainder != Chess::kRightSideRemainder)
    {
        unsigned int currentIndex = m_index += 1;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare)
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(currentIndex);
            }

            currentIndex += 1;
            int checkRemainder = currentIndex % Chess::kBoardWidth;
            if (currentIndex != Chess::kRightSideRemainder)
            {
                pSquare = &pGameState->GetSquare(currentIndex);
            }
            else
            {
                pSquare = nullptr;
            }
        }
    }

    //vertical moves
    // if rook isnt on top row then we can move up
    if (!(m_index < Chess::kBoardWidth))
    {
        unsigned int currentIndex = m_index -= Chess::kBoardHeight;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare)
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(currentIndex);
            }

            currentIndex -= Chess::kBoardHeight;

            if (currentIndex >= Chess::kBoardWidth)
            {
                pSquare = &pGameState->GetSquare(currentIndex);
            }
            else
            {
                pSquare = nullptr;
            }
        }
    }


    // if rook isnt on bottom row then we can move down
    if ((m_index > ((Chess::kBoardWidth * Chess::kBoardWidth)-1) - Chess::kBoardWidth))
    {
        unsigned int currentIndex = m_index += Chess::kBoardHeight;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare)
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(currentIndex);
            }

            currentIndex += Chess::kBoardHeight;

            if (currentIndex < (Chess::kBoardWidth * Chess::kBoardWidth) - (Chess::kBoardWidth))
            {
                pSquare = &pGameState->GetSquare(currentIndex);
            }
            else
            {
                pSquare = nullptr;
            }

        }
    }


    return moves;
}
