#include "ChessBoard.h"
#include <SDL.h>

void ChessBoard::StartGame()
{
   m_currentState.ResetBoard();
   m_currentState.SpawnPieces();
}

const int ChessBoard::GetCurrentPlayer() const
{
    return 0;
}

const int ChessBoard::GetAvailableMoves() const
{
    return 0;
}

void ChessBoard::MakeMove()
{
}

int ChessBoard::CheckForGameEnd() const
{
    return 0;
}

int ChessBoard::PrintGameEnd()
{
    return 0;
}

void ChessBoard::Render(SDL_Renderer* pRenderer)
{
    m_currentState.Render(pRenderer);
}
