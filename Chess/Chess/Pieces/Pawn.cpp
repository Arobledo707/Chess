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
    assert(Chess::IsValidIndex(m_index));
    Moves moves{};
    Square* pSquare = &pGameState->GetSquare(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset));
    bool spaceIsClear = pGameState->GetSquare(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)).GetPiece() == nullptr;
    if(HasMoved() == false && 
        pGameState->GetSquare(m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)).GetPiece() == nullptr &&
        pGameState->GetSquare(m_index + ((Chess::kBoardWidth) * m_moveOffset)).GetPiece() == nullptr)
    {
        moves.push_back(std::pair<int, int>((int)GetColor(), m_index + ((Chess::kBoardWidth * 2) * m_moveOffset)));
    }
    bool atTopRow = m_index < Chess::kBoardWidth;
    bool atBottomRow = m_index > ((Chess::kBoardSize) - 1) - Chess::kBoardWidth;

    if (!atTopRow || !atBottomRow)
    {
        if (pGameState->GetSquare(m_index + (Chess::kBoardWidth * m_moveOffset)).GetPiece() == nullptr)
        {
            int index = m_index + (Chess::kBoardWidth * m_moveOffset);
            moves.push_back(std::pair<int, int>((int)GetColor(), m_index + (Chess::kBoardWidth * m_moveOffset)));
        }

        int rightDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) + 1;
        int leftDiagonalIndex = m_index + (Chess::kBoardWidth * m_moveOffset) - 1;
        int remainder = m_index % Chess::kBoardWidth;

        if (remainder != Chess::kRightSideRemainder)
        {
            if (pGameState->GetSquare(rightDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(rightDiagonalIndex).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(std::pair<int, int>((int)GetColor(), rightDiagonalIndex));
            }
        }
        if (remainder != Chess::kLeftSideRemainder)
        {
            if (pGameState->GetSquare(leftDiagonalIndex).GetPiece() != nullptr &&
                pGameState->GetSquare(leftDiagonalIndex).GetPiece()->GetColor() != GetColor())
            {
                moves.push_back(std::pair<int, int>((int)GetColor(), leftDiagonalIndex));
            }
        }
    }
    return moves;
}
