#include "ChessBoard.h"
#include <SDL.h>

ChessBoard::ChessBoard()
{
}

void ChessBoard::StartGame()
{
   m_currentState.ResetBoard();
   //m_currentState.SpawnPieces();
   SpawnPieces();
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

void ChessBoard::SpawnPieces()
{
    SpawnPawns();
}

void ChessBoard::SpawnPawns()
{
    //TODO interate through half and instantiate 2 pawns at once?
//spawn white pawns
    unsigned int whitePawnIndexEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kWhitePawnColumn * Chess::kBoardWidth); i < whitePawnIndexEnd; ++i)
    {
        m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Pawn>
            (m_textureManager.GetTexture(Chess::Piece::kPawn, Chess::Color::kWhite), Chess::Color::kWhite, i), i);
    }

    unsigned int blackPawnIndexEnd = (Chess::kBlackPawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kBlackPawnColumn * Chess::kBoardWidth); i < blackPawnIndexEnd; ++i)
    {
        m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Pawn>
            (m_textureManager.GetTexture(Chess::Piece::kPawn, Chess::Color::kBlack), Chess::Color::kBlack, i), i);
    }

    unsigned int whitePawnPiecesEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
}

void ChessBoard::Initialize(SDL_Renderer* pRenderer)
{
    m_textureManager.CreateTextures(pRenderer);
}
