#include "Piece.h"
#include <cassert>

void Piece::Move(unsigned int move)
{
    assert(Chess::IsValidIndex(move));
    m_index = move;
    SetPosition((move % Chess::kBoardWidth) * Chess::kSquareWidth, (move / Chess::kBoardWidth) * Chess::kSquareWidth);
}
