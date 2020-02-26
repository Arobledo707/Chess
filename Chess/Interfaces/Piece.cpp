#include "Piece.h"
#include "../Chess/ChessGameState.h"
#include <cassert>
#include <iostream>

void Piece::Move(unsigned int move)
{
    assert(Chess::IsValidIndex(move));
    m_index = move;
    SetPosition((move % Chess::kBoardWidth) * Chess::kSquareWidth, (move / Chess::kBoardWidth) * Chess::kSquareWidth);
}

void Piece::CanCheck(Piece* pPiece)
{
    if (pPiece->GetType() == Chess::Piece::kKing) 
    {
        static_cast<King*>(pPiece)->SetCheck(true);
        std::cout << "King is in check" << std::endl;
    }
}

void Piece::AddMoveIfValid(unsigned int index, std::vector<unsigned int>& moves, ChessGameState* pGameState)
{
    Piece* pPiece = pGameState->GetSquare(index).GetPiece();
    if (!(pPiece && pPiece->GetColor() == GetColor()))
    {
        moves.push_back(index);
        CanCheck(pPiece);
    }
}
