#include "ChessBoard.h"
#include <SDL.h>
#include <ctime>

ChessBoard::ChessBoard()
    : m_selectedPiece(nullptr)
{
    std::srand(std::time(nullptr));
}

ChessBoard::ChessBoard(const ChessBoard& board)
{
    m_currentState = board.m_currentState;
}

ChessBoard& ChessBoard::operator=(const ChessBoard& board)
{
    m_currentState = board.m_currentState;
    return (*this);
}


int ChessBoard::StartGame()
{
    int aiNumber = AssignRoles();
    m_currentState.ResetBoard();
    SpawnPieces();
    return aiNumber;
}

const int ChessBoard::GetCurrentPlayer() const
{
    return static_cast<int>(m_currentTurn);
}

const Moves ChessBoard::GetAvailableMoves()
{
    Moves moves;
    for (auto& piece : m_currentState.GetPieces()) 
    {
        if (piece->GetColor() != m_currentTurn) 
        {
            continue;
        }
        Moves tempMoves = (piece->GetAvailableMoves(&m_currentState));
        for (Move& move : tempMoves) 
        {
            moves.push_back(move);
        }
    }
    return moves;
}

void ChessBoard::MakeMove(Move move)
{
    Piece* pPiece = m_currentState.GetSquare(move.second).GetPiece();
    if (m_selectedPiece == nullptr) 
    {
        m_selectedPiece = m_currentState.GetSquare(move.first).GetPiece();
        if (m_selectedPiece == nullptr) 
        {
            return;
        }
    }

    switch (m_selectedPiece->GetType())
    {
    case Chess::Piece::kKing:
        if (pPiece) 
        {
            bool isSameColorRook = pPiece->GetColor() == m_selectedPiece->GetColor() &&
                pPiece->GetType() == Chess::Piece::kRook;

            if (((isSameColorRook && !m_selectedPiece->HasMoved() 
                && !pPiece->HasMoved())))
            {
                m_currentState.GetSquare(m_selectedPiece->GetIndex()).SetPiece(pPiece);
                pPiece->Move(m_selectedPiece->GetIndex());
                break;
            }
        }
    case Chess::Piece::kPawn:
    default:
        if (pPiece)
        {
            m_currentState.RemovePiece(pPiece);
        }
        m_currentState.GetSquare(m_selectedPiece->GetIndex()).SetPiece(nullptr);
    }

    m_selectedPiece->Move(move.second);
    Square* pSquare = &m_currentState.GetSquare(move.second);
    pSquare->SetPiece(m_selectedPiece);
    m_moves.clear();
    m_selectedPiece = nullptr;
}

int ChessBoard::CheckForGameEnd() const
{
    if (m_currentState.GetBlackKing() == nullptr)
    {
        return (int)Chess::Color::kBlack;
    }
    if (m_currentState.GetWhiteKing() == nullptr)
    {
        return (int)Chess::Color::kWhite;
    }
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
        for (auto move : m_moves)
        {
            SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(pRenderer, 150, 0, 150, 128);
            SDL_RenderFillRect(pRenderer, &m_currentState.GetSquare(move.second).GetRect());
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
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 1:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 2:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kWhite), Chess::Color::kWhite, (Chess::kBoardWidth - 1) - i), (Chess::kBoardWidth - 1) - i);
            break;
        case 3:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<King>
                (m_textureManager.GetTexture(Chess::Piece::kKing, Chess::Color::kWhite), Chess::Color::kWhite, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Queen>
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
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 57:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 58:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, Chess::Color::kBlack), Chess::Color::kBlack, maxIndex - j), maxIndex - j);
            break;
        case 59:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<King>
                (m_textureManager.GetTexture(Chess::Piece::kKing, Chess::Color::kBlack), Chess::Color::kBlack, i), i);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Queen>
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
        m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Pawn>
            (m_textureManager.GetTexture(Chess::Piece::kPawn, Chess::Color::kWhite), Chess::Color::kWhite, i), i);
    }

    unsigned int blackPawnIndexEnd = (Chess::kBlackPawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kBlackPawnColumn * Chess::kBoardWidth); i < blackPawnIndexEnd; ++i)
    {
        m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Pawn>
            (m_textureManager.GetTexture(Chess::Piece::kPawn, Chess::Color::kBlack), Chess::Color::kBlack, i), i);
    }

    unsigned int whitePawnPiecesEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
}

int ChessBoard::AssignRoles()
{
    // if player is 0 then player is white
    int playerColor = std::rand() % 2;
    if (playerColor == 0) 
    {
        m_playerColor = Chess::Color::kWhite;
        return int(Chess::Color::kBlack);
    }
    else 
    {
        m_playerColor = Chess::Color::kBlack;
        return int(Chess::Color::kWhite);
    }
}

const int ChessBoard::GetPlayerColor() const
{
    return static_cast<int>(m_playerColor);
}

void ChessBoard::AlternateTurns()
{
    if (m_currentTurn == Chess::Color::kBlack) 
    {
        m_currentTurn = Chess::Color::kWhite;
    } 
    else
    {
        m_currentTurn = Chess::Color::kBlack;
    }
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
            if (index == m_moves[i].second)
            {
                MakeMove(std::pair<int, int>((int)m_currentTurn, index));
                AlternateTurns();
                return true;
            }
        }
        m_selectedPiece = nullptr;
        m_moves.clear();
    }

    m_selectedPiece = m_currentState.GetSquare(index).GetPiece();
    if (m_selectedPiece)
    {
        if (m_selectedPiece->GetColor() != m_currentTurn)
        {
            return false;
        }
        m_moves = m_selectedPiece->GetAvailableMoves(&m_currentState);
    }

    return false;
}

Board* ChessBoard::CloneSelf() const
{
    ChessBoard* pChessBoard = new ChessBoard(*this);
    return pChessBoard;
}

void ChessBoard::Initialize(SDL_Renderer* pRenderer)
{
    m_textureManager.CreateTextures(pRenderer);
}
