#include "ChessGameState.h"
#include <algorithm>
#include <iostream>
#include <SDL.h>
#include "../Chess/Factory/PieceFactory.h"
#include "../Chess/Pieces/Pawn.h"
#include "../Constants/ChessConstants.h"

ChessGameState::ChessGameState()
{
    // CREATEBOARD NOT RESET
    // CREATE PIECES
    // reset board can clear pieces then create them
    //m_textureManager.CreateTextures();
    m_pieceFactory = std::make_unique<PieceFactory>();
    m_pieces.reserve(Chess::kChessPieces);
    ResetBoard();
}

void ChessGameState::SpawnPieces(const SDLTextureManager& textureManager)
{
    //SpawnPawns(textureManager);
}

void ChessGameState::Render(SDL_Renderer* pRenderer)
{

    for (const Square& square: m_squares) 
    {
        square.Render(pRenderer);
    }

    for (const auto& piece: m_pieces) 
    {
        piece.get()->Render(pRenderer);
    }

}

void ChessGameState::AddPiece(std::unique_ptr<Piece> piece, unsigned int i)
{
    m_pieces.push_back(std::move(piece));
    m_squares[i].SetPiece(m_pieces.back().get());
}

Square& ChessGameState::GetSquare(unsigned int index)
{
    return m_squares[index];
}

void ChessGameState::RemovePiece(Piece* pPiece)
{
    for (int i = 0; i < m_pieces.size(); ++i) 
    {
        if (pPiece == m_pieces[i].get())
        {
            std::swap(m_pieces[i], m_pieces.back());
            m_pieces.pop_back();
            break;
        }
    }
}

void ChessGameState::AddPiece()
{
}


void ChessGameState::ResetBoard()
{
    //std::fill(&m_squares[0], &m_squares[0] + sizeof(m_squares)/sizeof(Square), Square());
    //PieceFactory pf;
    //pf.ReturnUnique<Pawn>();
    
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
