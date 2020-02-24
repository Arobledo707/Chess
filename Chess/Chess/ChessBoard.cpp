#include "ChessBoard.h"
#include <SDL.h>

ChessBoard::ChessBoard()
    : m_selectedPiece(nullptr)
{
}

void ChessBoard::StartGame()
{
    m_currentState.ResetBoard();
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

void ChessBoard::MakeMove(unsigned int move)
{
    Piece* pPiece = m_currentState.GetSquare(move).GetPiece();
    if (pPiece) 
    {
        m_currentState.RemovePiece(pPiece);
    }
    m_currentState.GetSquare(m_selectedPiece->GetIndex()).SetPiece(nullptr);
    m_selectedPiece->Move(move);
    Square* pSquare = &m_currentState.GetSquare(move);
    pSquare->SetPiece(m_selectedPiece);
    m_moves.clear();
    m_selectedPiece = nullptr;
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
    if (!m_moves.empty())
    {
        for (unsigned int move: m_moves)
        {
            SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(pRenderer, 150, 0, 150, 128);
            SDL_RenderFillRect(pRenderer, &m_currentState.GetSquare(move).GetRect());
        }
    }
}

void ChessBoard::SpawnPieces()
{
    SpawnPawns();

    //TODO refactor into a function

    for (int i = 0; i < Chess::kBoardWidth / 2; ++i)
    {
        switch (i)
        {
        case 0:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 1:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 2:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 3:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<King>
                (m_textureManager.GetTexture(Chess::Piece::kKing, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Queen>
                (m_textureManager.GetTexture(Chess::Piece::kQueen, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
        }
    }

    int maxIndex = Chess::kBoardWidth * Chess::kBoardWidth - 1;

    for (int j = 0; j < Chess::kBoardWidth / 2; ++j)
    {
        int i = (Chess::kBoardWidth * Chess::kBlackPieceRow) + j;
        switch (i)
        {
        case 56:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 57:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 58:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 59:
            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<King>
                (m_textureManager.GetTexture(Chess::Piece::kKing, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.get()->ReturnPiece<Queen>
                (m_textureManager.GetTexture(Chess::Piece::kQueen, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
        }
    }
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

const bool ChessBoard::OnClick()
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);
    int column = x / Chess::kSquareWidth;
    int row = y / Chess::kSquareWidth;

    int index = (row * Chess::kBoardWidth) + column;

    if (m_selectedPiece)
    {
        for (int i = 0; i < m_moves.size(); ++i)
        {
            if (index == m_moves[i])
            {
                MakeMove(index);
                return true;
            }
        }
        m_selectedPiece = nullptr;
        m_moves.clear();
    }

    m_selectedPiece = m_currentState.GetSquare(index).GetPiece();
    if (m_selectedPiece)
    {
        m_moves = m_selectedPiece->GetAvailableMoves(&m_currentState);
    }

    return false;
}

void ChessBoard::Initialize(SDL_Renderer* pRenderer)
{
    m_textureManager.CreateTextures(pRenderer);
}
