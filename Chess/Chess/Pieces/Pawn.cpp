#include "Pawn.h"
#include "../ChessGameState.h"

Pawn::Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
    if (GetColor() == Chess::Color::kBlack) 
    {
        m_moveOffset *= -1;
    }
}

void Pawn::Move()
{
    m_hasMoved = true;
}


std::vector<unsigned int> Pawn::GetAvailableMoves(ChessGameState* pGameState)
{
    std::vector<unsigned int> moves{};
    if(m_hasMoved == false)
    {
        moves.push_back(m_index + (Chess::kBoardWidth * 2));
    }

    if (!(m_index < Chess::kBoardWidth) || !(m_index > ((Chess::kBoardWidth * Chess::kBoardWidth) - 1) - Chess::kBoardWidth)) 
    {
        if (pGameState->GetSquare(m_index + Chess::kBoardWidth).GetPiece() == nullptr)
        {
            moves.push_back(m_index + Chess::kBoardWidth);
        }

        unsigned int rightDiagonalIndex = m_index + Chess::kBoardWidth + 1;
        unsigned int leftDiagonalIndex = m_index + Chess::kBoardWidth - 1;
        unsigned int remainder = m_index % Chess::kBoardWidth;

        if (remainder != Chess::kRightSideRemainder)
        {
            if (pGameState->GetSquare(rightDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(m_index + Chess::kBoardWidth + 1).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(rightDiagonalIndex);
            }
        }
        if (remainder != Chess::kLeftSideRemainder)
        {
            if (pGameState->GetSquare(leftDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(m_index + Chess::kBoardWidth + 1).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(leftDiagonalIndex);
            }
        }
    }
    return moves;
}
