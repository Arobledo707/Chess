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


Moves King::GetAvailableMoves(ChessGameState* pGameState)
{
    Moves moves;
    int kingMovement = 1;

    if (!HasMoved()) 
    {
        unsigned int leftRook = 3;
        unsigned int rightRook = 4;
        // check if we can castle 

        // left side castle
        if (CanCastle(leftRook, true, pGameState)) 
        {
            moves.push_back(std::pair<int, int>((int)GetColor(), m_index - leftRook));
        }

        //right side castle
        if (CanCastle(rightRook, false, pGameState)) 
        {
            moves.push_back(std::pair<int, int>((int)GetColor(), m_index + rightRook));
        }
    }
    int remainder = m_index % Chess::kBoardWidth;

    if (remainder != Chess::kLeftSideRemainder) 
    {
        // move left
        AddMoveIfValid(m_index - kingMovement, moves, pGameState);

        // move down to the left
        if (Chess::IsValidIndex((m_index - kingMovement) + Chess::kBoardWidth)) 
        {
            AddMoveIfValid(m_index - kingMovement + Chess::kBoardWidth, moves, pGameState);
        }

        // move up to the left
        if (Chess::IsValidIndex((m_index - kingMovement) - Chess::kBoardWidth))
        {
            AddMoveIfValid(m_index - kingMovement - Chess::kBoardWidth, moves, pGameState);
        }
    }

    if (remainder != Chess::kRightSideRemainder) 
    {
        // move right
        AddMoveIfValid(m_index + kingMovement, moves, pGameState);

        // move down to the right
        if (Chess::IsValidIndex((m_index + kingMovement) + Chess::kBoardWidth))
        {
            AddMoveIfValid(m_index + kingMovement + Chess::kBoardWidth, moves, pGameState);
        }

        // move up to the right
        if (Chess::IsValidIndex((m_index + kingMovement) - Chess::kBoardWidth))
        {
            AddMoveIfValid((m_index + kingMovement) - Chess::kBoardWidth, moves, pGameState);
        }
    }

    // move down
    if (Chess::IsValidIndex(m_index + Chess::kBoardWidth)) 
    {
        AddMoveIfValid(m_index + Chess::kBoardWidth, moves, pGameState);
    }

    // move up
    if (Chess::IsValidIndex(m_index - Chess::kBoardWidth))
    {
        AddMoveIfValid(m_index - Chess::kBoardWidth, moves, pGameState);
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
