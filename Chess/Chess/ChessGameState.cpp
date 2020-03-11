#include "ChessGameState.h"
#include <algorithm>
#include <iostream>
#include <SDL.h>
#include "../Chess/Factory/PieceFactory.h"
#include "../Chess/Pieces/Pawn.h"
#include "../Constants/ChessConstants.h"
#include "../Interfaces/Piece.h"

ChessGameState::ChessGameState()
{
    // CREATEBOARD NOT RESET
    // CREATE PIECES
    // reset board can clear pieces then create them
    //m_textureManager.CreateTextures();
    m_pieces.reserve(Chess::kChessPieces);
    ResetBoard();
}

ChessGameState::~ChessGameState()
{
    for (Piece* piece : m_pieces)
    {
        delete piece;
        piece = nullptr;
    }
}

ChessGameState::ChessGameState(const ChessGameState& state)
{
    Copy(state);
}

ChessGameState& ChessGameState::operator=(const ChessGameState& state)
{
    Copy(state);
    return(*this);
}

void ChessGameState::Copy(const ChessGameState& cgs)
{
    memcpy(m_squares, cgs.m_squares, sizeof(Square) * Chess::kBoardSize);
    memcpy(&m_pieces, &cgs.m_pieces, sizeof(std::unique_ptr<Piece>) * cgs.m_pieces.size());
    m_pBlackKing = cgs.m_pBlackKing;
    m_pWhiteKing = cgs.m_pWhiteKing;

}


void ChessGameState::Render(SDL_Renderer* pRenderer)
{
    for (const Square& square : m_squares)
    {
        square.Render(pRenderer);
    }

    for (const auto& piece : m_pieces)
    {
        piece->Render(pRenderer);
    }

}

void ChessGameState::AddPiece(Piece* piece, unsigned int i)
{
    if (piece->GetType() == Chess::Piece::kKing)
    {
        if (piece->GetColor() == Chess::Color::kBlack)
        {
            m_pBlackKing = dynamic_cast<King*>(piece);
        }
        else
        {
            m_pWhiteKing = dynamic_cast<King*>(piece);
        }
    }
    m_pieces.push_back(std::move(piece));
    m_squares[i].SetPiece(m_pieces.back());
}

Square& ChessGameState::GetSquare(unsigned int index)
{
    return m_squares[index];
}

void ChessGameState::RemovePiece(Piece* pPiece)
{
    for (unsigned int i = 0U; i < m_pieces.size(); ++i)
    {
        if (pPiece == m_pieces[i])
        {
            if (pPiece->GetType() == Chess::Piece::kKing)
            {
                if (pPiece->GetColor() == Chess::Color::kWhite)
                {
                    m_pWhiteKing = nullptr;
                }
                else
                {
                    m_pBlackKing = nullptr;
                }
            }
            delete m_pieces[i];
            m_pieces[i] = nullptr;
            std::swap(m_pieces[i], m_pieces.back());
            m_pieces.pop_back();
            break;
        }
    }
}

void ChessGameState::ReplacePiece(Piece* pPiece, Chess::Piece type, SDLTextureManager* pTexManager)
{
    assert(pPiece);
    Piece* pNewPiece = nullptr;
    int index = pPiece->GetIndex();
    Chess::Color color = pPiece->GetColor();
    PieceFactory peaceFactory;
    switch (type)
    {
    case Chess::Piece::kKnight:
        pNewPiece = peaceFactory.ReturnPiece<Knight>(pTexManager->GetTexture(type, color), color, index);
        break;
    case Chess::Piece::kBishop:
        pNewPiece = peaceFactory.ReturnPiece<Bishop>(pTexManager->GetTexture(type, color), color, index);
        break;
    case Chess::Piece::kRook:
        pNewPiece = peaceFactory.ReturnPiece<Rook>(pTexManager->GetTexture(type, color), color, index);
        break;
    case Chess::Piece::kQueen:
        pNewPiece = peaceFactory.ReturnPiece<Queen>(pTexManager->GetTexture(type, color), color, index);
        break;
    default:
        std::cout << "Error: AddPiece type was not valid" << std::endl;
        break;
    }
    if (pNewPiece)
    {
        RemovePiece(pPiece);
        AddPiece(pNewPiece, index);
    }
}


void ChessGameState::ResetBoard()
{
    Square::Color currentColor = Square::Color::Black;
    std::pair<char, int> currentId = std::make_pair('a', 1);

    unsigned int blackSquareCounter = 0;
    unsigned int whiteSquareCounter = 0;
    unsigned int index = 0;
    for (int y = 0; y < Chess::kBoardHeight; ++y)
    {
        for (int x = 0; x < Chess::kBoardWidth; ++x)
        {
            index = (y * Chess::kBoardWidth) + x;
            m_squares[index] = Square(currentColor, currentId, Chess::kSquareWidth * x, Chess::kSquareWidth * y);;
            currentId.second += 1;
            if (currentColor == Square::Color::Black)
            {
                currentColor = Square::Color::White;
            }
            else
            {
                currentColor = Square::Color::Black;
            }
        }
        if (currentColor == Square::Color::Black)
        {
            currentColor = Square::Color::White;
        }
        else
        {
            currentColor = Square::Color::Black;
        }
        currentId = std::make_pair(currentId.first + 1, 0);

    }
}
