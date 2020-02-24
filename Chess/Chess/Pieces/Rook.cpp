#include "Rook.h"
#include "../ChessGameState.h"

Rook::Rook(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kRook), m_hasMoved(false)
{
}

void Rook::Move(unsigned int move)
{
    m_hasMoved = true;
    Piece::Move(move);
}


std::vector<unsigned int> Rook::GetAvailableMoves(ChessGameState* pGameState)
{
    assert(Chess::IsValidIndex(m_index));

    std::vector<unsigned int> moves{};

    //horizontal moves
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
                    moves.push_back(currentIndex);
                    break;
                }
            }
            moves.push_back(currentIndex);
        }

    }

    // if the remainder isn't 0 then we can move left
    //if (remainder != Chess::kLeftSideRemainder)
    //{
    //    unsigned int currentIndex = m_index - 1;
    //    Square* pSquare = &pGameState->GetSquare(currentIndex);

    //    while (pSquare) 
    //    {
    //        Piece* pPiece = pSquare->GetPiece();
    //        if (pPiece == nullptr || pPiece->GetColor() != GetColor()) 
    //        {
    //            moves.push_back(currentIndex);
    //        }
    //        else 
    //        {
    //            break;
    //        }

    //        currentIndex -= 1;
    //        int checkRemainder = currentIndex % Chess::kBoardWidth;
    //        if (checkRemainder > Chess::kLeftSideRemainder)
    //        {
    //            pSquare = &pGameState->GetSquare(currentIndex);
    //        }
    //        else if(checkRemainder == Chess::kLeftSideRemainder) 
    //        {
    //            Piece* pPiece = pSquare->GetPiece();
    //            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
    //            {
    //                moves.push_back(currentIndex);
    //            }
    //            break;
    //        }
    //        else 
    //        {
    //            pSquare = nullptr;
    //        }
    //    }

    //}

    // if the remainder isn't 7 then we can move right
    if (remainder != Chess::kRightSideRemainder)
    {
        unsigned int currentIndex = m_index + 1;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare)
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(currentIndex);
            }
            else
            {
                break;
            }

            currentIndex += 1;
            int checkRemainder = currentIndex % Chess::kBoardWidth;
            if (checkRemainder < Chess::kRightSideRemainder)
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
                    moves.push_back(currentIndex);
                    break;
                }
            }
            moves.push_back(currentIndex);
            if (currentIndex < Chess::kBoardWidth)
            {
                break;
            }
            currentIndex -= Chess::kBoardWidth;
        }

    }

    //vertical moves
    // if rook isnt on top row then we can move up
    //if (!(m_index < Chess::kBoardWidth))
    //{
    //    unsigned int currentIndex = m_index - Chess::kBoardHeight;
    //    Square* pSquare = &pGameState->GetSquare(currentIndex);

    //    while (pSquare)
    //    {
    //        Piece* pPiece = pSquare->GetPiece();
    //        if (pPiece == nullptr || pPiece->GetColor() != GetColor())
    //        {
    //            moves.push_back(currentIndex);
    //        }
    //        else 
    //        {
    //            break;
    //        }
    //        currentIndex -= Chess::kBoardHeight;

    //        if (currentIndex >= Chess::kBoardWidth)
    //        {
    //            pSquare = &pGameState->GetSquare(currentIndex);
    //        }
    //        else
    //        {
    //            pSquare = nullptr;
    //        }
    //    }
    //}


    // if rook isnt on bottom row then we can move down
    if ((m_index < ((Chess::kBoardSize) - 1) - Chess::kBoardWidth))
    {
        unsigned int currentIndex = m_index + Chess::kBoardHeight;
        Square* pSquare = &pGameState->GetSquare(currentIndex);

        while (pSquare)
        {
            Piece* pPiece = pSquare->GetPiece();
            if (pPiece == nullptr || pPiece->GetColor() != GetColor())
            {
                moves.push_back(currentIndex);
            }
            else
            {
                break;
            }

            currentIndex += Chess::kBoardHeight;

            if (currentIndex < (Chess::kBoardSize - 1) - (Chess::kBoardWidth))
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
