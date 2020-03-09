#include "Piece.h"
#include "../Chess/ChessGameState.h"
#include <cassert>
#include <iostream>

Piece::Piece(const Piece& piece)
    : m_color(piece.m_color)
{
    m_type = piece.GetType();
    m_hasMoved = piece.m_hasMoved;
    m_rect = piece.m_rect;
    m_index = piece.m_index;
    m_pTexture = piece.m_pTexture;
}

Piece& Piece::operator=(const Piece& piece)
{
    m_type = piece.GetType();
    m_hasMoved = piece.m_hasMoved;
    m_rect = piece.m_rect;
    m_index = piece.m_index;
    m_pTexture = piece.m_pTexture;
    return (*this);
}

Piece& Piece::operator=(Piece&& piece)
{
     return (piece);
}

void Piece::Move(unsigned int move)
{
    assert(Chess::IsValidIndex(move));
    m_index = move;
    SetPosition((move % Chess::kBoardWidth) * Chess::kSquareWidth, (move / Chess::kBoardWidth) * Chess::kSquareWidth);
}

void Piece::CanCheck(Piece* pPiece)
{
    if (pPiece)
    {
        if (pPiece->GetType() == Chess::Piece::kKing)
        {
            static_cast<King*>(pPiece)->SetCheck(true);
            std::cout << "King is in check" << std::endl;
        }
    }
}

void Piece::AddMoveIfValid(unsigned int index, Moves& moves, ChessGameState* pGameState)
{
    Piece* pPiece = pGameState->GetSquare(index).GetPiece();
    if (!(pPiece && pPiece->GetColor() == GetColor()))
    {
        moves.push_back(std::pair<int, int>(m_index, index));
        CanCheck(pPiece);
    }
}
