#include "Piece.h"
#include "../Chess/ChessGameState.h"
#include <cassert>

void Piece::Move(unsigned int move)
{
    assert(Chess::IsValidIndex(move));
    m_index = move;
    SetPosition((move % Chess::kBoardWidth) * Chess::kSquareWidth, (move / Chess::kBoardWidth) * Chess::kSquareWidth);
}

void Piece::AddMoveIfValid(unsigned int index, std::vector<unsigned int>& moves, ChessGameState* pGameState)
{
    Piece* pPiece = pGameState->GetSquare(index).GetPiece();
    if (!(pPiece && pPiece->GetColor() == GetColor()))
    {
        moves.push_back(index);
    }
}
