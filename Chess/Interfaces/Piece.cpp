#include "Piece.h"

void Piece::Move(unsigned int move)
{
    m_index = move;
    SetPosition((move % Chess::kBoardWidth) * Chess::kSquareWidth, (move / Chess::kBoardWidth) * Chess::kSquareWidth);
}
