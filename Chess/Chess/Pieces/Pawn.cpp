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
    SetMoved();
    Piece::Move(move);
}


Moves Pawn::GetAvailableMoves(ChessGameState* pGameState)
{
    Moves moves{};
    if(HasMoved() == false && 
        pGameState->GetSquare(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)).GetPiece() == nullptr &&
        pGameState->GetSquare(m_index + ((Chess::kBoardWidth) * m_moveOffset)).GetPiece() == nullptr)
    {
        moves.push_back(std::pair<int, int>(m_index, m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)));
    }
    bool atTopRow = m_index < Chess::kBoardWidth;
    bool atBottomRow = m_index > ((Chess::kBoardSize) - 1) - Chess::kBoardWidth;

    if (!atTopRow || !atBottomRow)
    {
        if (pGameState->GetSquare(m_index + (Chess::kBoardWidth * m_moveOffset)).GetPiece() == nullptr)
        {
            int move = m_index + (Chess::kBoardWidth * m_moveOffset);
            moves.push_back(std::pair<int, int>(m_index, m_index + (Chess::kBoardWidth * m_moveOffset)));
        }

        unsigned int rightDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) + 1;
        unsigned int leftDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) - 1;
        unsigned int remainder = m_index % Chess::kBoardWidth;

        if (remainder != Chess::kRightSideRemainder)
        {
            if (pGameState->GetSquare(rightDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(rightDiagonalIndex).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(std::pair<int, int>(m_index, rightDiagonalIndex));
            }
        }
        if (remainder != Chess::kLeftSideRemainder)
        {
            if (pGameState->GetSquare(leftDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(leftDiagonalIndex).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(std::pair<int, int>(m_index, leftDiagonalIndex));
            }
        }
    }
    return moves;
}
