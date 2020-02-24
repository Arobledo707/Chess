#include "Pawn.h"
#include "../ChessGameState.h"

Pawn::Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index, Chess::Piece::kPawn)
{
    if (GetColor() == Chess::Color::kBlack) 
    {
        m_moveOffset *= -1;
    }
}

void Pawn::Move(unsigned int move)
{
    m_hasMoved = true;
    Piece::Move(move);
}


std::vector<unsigned int> Pawn::GetAvailableMoves(ChessGameState* pGameState)
{
    std::vector<unsigned int> moves{};
    if(m_hasMoved == false && pGameState->GetSquare(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)).GetPiece() == nullptr)
    {
        moves.push_back(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset));
    }

    if (!(m_index < Chess::kBoardWidth) || !(m_index > ((Chess::kBoardSize) - 1) - Chess::kBoardWidth)) 
    {
        if (pGameState->GetSquare(m_index + (Chess::kBoardWidth * m_moveOffset)).GetPiece() == nullptr)
        {
            moves.push_back(m_index + (Chess::kBoardWidth * m_moveOffset));
        }

        unsigned int rightDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) + 1;
        unsigned int leftDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) - 1;
        unsigned int remainder = m_index % Chess::kBoardWidth;

        if (remainder != Chess::kRightSideRemainder)
        {
            if (pGameState->GetSquare(rightDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(m_index + (Chess::kBoardWidth * m_moveOffset) + 1).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(rightDiagonalIndex);
            }
        }
        if (remainder != Chess::kLeftSideRemainder)
        {
            if (pGameState->GetSquare(leftDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(m_index + (Chess::kBoardWidth * m_moveOffset) + 1).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(leftDiagonalIndex);
            }
        }
    }
    return moves;
}
