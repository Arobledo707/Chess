#include "ChessBoard.h"
#include <SDL.h>
#include <ctime>
#include <conio.h>
#include <cctype>

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
    {
        int index = move.second;
        if (index < Chess::kBoardWidth || index > Chess::kBoardSize - Chess::kBoardWidth)
        {
            PromotePawn();
            m_selectedPiece = m_currentState.GetPieces().back();
        }
        //break;
    }
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
    m_pastMoves.push_back(move);
}

int ChessBoard::CheckForGameEnd() const
{
    if (m_currentState.GetBlackKing() == nullptr)
    {
        return (int)Chess::Color::kWhite;
    }
    if (m_currentState.GetWhiteKing() == nullptr)
    {
        return (int)Chess::Color::kBlack;
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
            SDL_SetRenderDrawColor(pRenderer, Chess::kPurple.r, Chess::kPurple.g, Chess::kPurple.b, Chess::kPurple.a);
            SDL_RenderFillRect(pRenderer, &m_currentState.GetSquare(move.second).GetRect());
        }
    }
}

void ChessBoard::PromotePawn()
{
    bool hasPicked = false;
    Chess::Piece type = Chess::Piece::kQueen;
    //if (m_playerColor == m_currentTurn)
    //{
        //while (!hasPicked)
        //{
        //    char input = _getch();
        //    input = std::toupper(input);
        //    switch (input)
        //    {
        //        case static_cast<char>(Chess::Piece::kBishop) :
        //            type = Chess::Piece::kBishop;
        //            break;
        //        case static_cast<char>(Chess::Piece::kKnight) :
        //            type = Chess::Piece::kKnight;
        //            break;
        //        case static_cast<char>(Chess::Piece::kQueen) :
        //            type = Chess::Piece::kQueen;
        //            break;
        //        case static_cast<char>(Chess::Piece::kRook) :
        //            type = Chess::Piece::kRook;
        //            break;
        //    }
        //}

        if (type != Chess::Piece::kInvalid)
        {
            m_currentState.ReplacePiece(m_selectedPiece, type, &m_textureManager);
            hasPicked = true;
        }
    //}
}

void ChessBoard::SpawnPieces()
{
    SpawnPawns();
    SpawnNonPawns(Chess::Color::kWhite, (Chess::kBoardWidth - 1), 0);
    SpawnNonPawns(Chess::Color::kBlack, Chess::kBoardSize - 1, Chess::kBoardSize - Chess::kBoardWidth);
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

    // spawn black pawns
    unsigned int blackPawnIndexEnd = (Chess::kBlackPawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kBlackPawnColumn * Chess::kBoardWidth); i < blackPawnIndexEnd; ++i)
    {
        m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Pawn>
            (m_textureManager.GetTexture(Chess::Piece::kPawn, Chess::Color::kBlack), Chess::Color::kBlack, i), i);
    }

    unsigned int whitePawnPiecesEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
}

// terrible function name but this spawns rooks, knights, bishops, king and queen
void ChessBoard::SpawnNonPawns(Chess::Color color, int maxIndex, int lowIndex)
{
    for (int i = 0; i < Chess::kBoardWidth / 2; ++i)
    {
        if (color == Chess::Color::kWhite)
        {
            lowIndex = i;
        }
        else
        {
            lowIndex = (Chess::kBoardWidth * Chess::kBlackPieceRow) + i;
        }
        switch (i)
        {
        case 0:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, color), color, lowIndex), lowIndex);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Rook>
                (m_textureManager.GetTexture(Chess::Piece::kRook, color), color, maxIndex - i), maxIndex - i);
            break;
        case  1:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, color), color, lowIndex), lowIndex);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Knight>
                (m_textureManager.GetTexture(Chess::Piece::kKnight, color), color, maxIndex - i), maxIndex - i);
            break;
        case 2:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, color), color, lowIndex), lowIndex);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Bishop>
                (m_textureManager.GetTexture(Chess::Piece::kBishop, color), color, maxIndex - i), maxIndex - i);
            break;
        case 3:
            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<King>
                (m_textureManager.GetTexture(Chess::Piece::kKing, color), color, lowIndex), lowIndex);

            m_currentState.AddPiece(m_pieceFactory.ReturnPiece<Queen>
                (m_textureManager.GetTexture(Chess::Piece::kQueen, color), color, maxIndex - i), maxIndex - i);
        }
    }
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
