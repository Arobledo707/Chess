#include "King.h"
#include "../ChessGameState.h"
King::King(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kKing)
{
}

void King::Move(unsigned int move)
{
    SetMoved();
    Piece::Move(move);
}


std::vector<unsigned int> King::GetAvailableMoves(ChessGameState* pGameState)
{
    std::vector<unsigned int> moves;
    int kingMovement = 1;

    //todo refactor castling
    if (!HasMoved()) 
    {
        unsigned int leftRook = 3;
        unsigned int rightRook = 4;
        // check if we can castle 

        // left side castle
        if (CanCastle(leftRook, true, pGameState)) 
        {
            moves.push_back(m_index - leftRook);
        }

        //right side castle
        if (CanCastle(rightRook, false, pGameState)) 
        {
            moves.push_back(m_index + rightRook);
        }

    }
    int remainder = m_index % Chess::kBoardWidth;

    if (remainder != Chess::kLeftSideRemainder) 
    {
        // move left
        Piece* pPiece = pGameState->GetSquare(m_index - kingMovement).GetPiece();
        if (!(pPiece && pPiece->GetColor() == GetColor())) 
        {
            moves.push_back(m_index - kingMovement);
        }

        // move down to the left
        if (Chess::IsValidIndex((m_index - kingMovement) + Chess::kBoardWidth)) 
        {
            pPiece = pGameState->GetSquare((m_index - kingMovement) + Chess::kBoardWidth).GetPiece();
            if (!(pPiece && pPiece->GetColor() == GetColor()))
            {
                moves.push_back((m_index - kingMovement) + Chess::kBoardWidth);
            }
        }

        // move up to the left
        if (Chess::IsValidIndex((m_index - kingMovement) - Chess::kBoardWidth))
        {
            pPiece = pGameState->GetSquare((m_index - kingMovement) - Chess::kBoardWidth).GetPiece();
            if (!(pPiece && pPiece->GetColor() == GetColor()))
            {
                moves.push_back((m_index - kingMovement) - Chess::kBoardWidth);
            }
        }
    }

    if (remainder != Chess::kRightSideRemainder) 
    {
        // move right
        Piece* pPiece = pGameState->GetSquare(m_index + kingMovement).GetPiece();
        if (!(pPiece && pPiece->GetColor() == GetColor()))
        {
            moves.push_back(m_index + kingMovement);
        }

        // move down to the right
        if (Chess::IsValidIndex((m_index + kingMovement) + Chess::kBoardWidth))
        {
            pPiece = pGameState->GetSquare((m_index + kingMovement) + Chess::kBoardWidth).GetPiece();
            if (!(pPiece && pPiece->GetColor() == GetColor()))
            {
                moves.push_back((m_index + kingMovement) + Chess::kBoardWidth);
            }
        }

        // move up to the right
        if (Chess::IsValidIndex((m_index + kingMovement) - Chess::kBoardWidth))
        {
            pPiece = pGameState->GetSquare((m_index + kingMovement) - Chess::kBoardWidth).GetPiece();
            if (!(pPiece && pPiece->GetColor() == GetColor()))
            {
                moves.push_back((m_index + kingMovement) - Chess::kBoardWidth);
            }
        }
    }

    // move down
    if (Chess::IsValidIndex(m_index + Chess::kBoardWidth)) 
    {
        Piece* pPiece = pGameState->GetSquare(m_index + Chess::kBoardWidth).GetPiece();
        if (!(pPiece && pPiece->GetColor() == GetColor()))
        {
            moves.push_back(m_index + Chess::kBoardWidth);
        }
    }

    // move up
    if (Chess::IsValidIndex(m_index - Chess::kBoardWidth))
    {
        Piece* pPiece = pGameState->GetSquare(m_index - Chess::kBoardWidth).GetPiece();
        if (!(pPiece && pPiece->GetColor() == GetColor()))
        {
            moves.push_back(m_index - Chess::kBoardWidth);
        }
    }

    return moves;
}

bool King::CanCastle(int index, bool leftSide, ChessGameState* pGameState)
{
    int factor = 1;
    if (leftSide) 
    {
        factor = -1;
    }

    Piece* pPiece = pGameState->GetSquare(m_index + (factor * index)).GetPiece();
    bool rookAvailable = pPiece && pPiece->GetType() == Chess::Piece::kRook &&
        pPiece->GetColor() == GetColor() && !pPiece->HasMoved();

    bool clearPath = true;

    for (int i = 1; i < index; ++i)
    {
        if (pGameState->GetSquare(m_index + (factor * i)).GetPiece())
        {
            clearPath = false;
            break;
        }
    }

    if (rookAvailable && clearPath)
    {
        return true;
    }

    return false;
}
