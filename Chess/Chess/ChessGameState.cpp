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
    m_pieceFactory = std::make_unique<PieceFactory>();
    m_pieces.reserve(Chess::kChessPieces);
    ResetBoard();
}

void ChessGameState::Render(SDL_Renderer* pRenderer) const
{
    //for (const Square* square: m_blackSquares) 
    //{
    //    square->Render(pRenderer);
    //}

    //SDL_SetRenderDrawColor(pRenderer, 0, 150, 150, 0);

    //for (const Square* square : m_whiteSquares)
    //{
    //    square->Render(pRenderer);
    //}

    for (const Square& square: m_squares) 
    {
        square.Render(pRenderer);
    }

}

bool ChessGameState::CheckColumns(int column)
{
    if (column == Chess::kBlackPawnColumn || column == Chess::kWhitePawnColumn
        || column == Chess::kBlackPieceColumnn || column ==Chess::kWhitePieceColumn) 
    {
        return true;
    }
    return false;
}

std::shared_ptr<Piece> ChessGameState::SpawnPawn(Chess::Color color, unsigned int index)
{
    return m_pieceFactory.get()->ReturnPiece<Pawn>(nullptr, color, index);
    //m_pieceFactory.get()->ReturnChessPiece<Chess::Piece::kPawn, Piece>(nullptr, color, index);
}   

std::shared_ptr<Piece> ChessGameState::SpawnPiece(int column, int row)
{
    std::shared_ptr<Piece> piece;
    if (column == Chess::kBlackPawnColumn) 
    {
        piece = SpawnPawn(Chess::Color::kBlack, (column * Chess::kBoardWidth) + row);
    }

    else if(column == Chess::kWhitePawnColumn) 
    {
        piece = SpawnPawn(Chess::Color::kWhite, (column * Chess::kBoardWidth) + row);

    }

    else if (column == Chess::kBlackPieceColumnn) 
    {

    }
    else if (column == Chess::kWhitePieceColumn) 
    {

    }

    return piece;
}

void ChessGameState::ResetBoard()
{
    //std::fill(&m_squares[0], &m_squares[0] + sizeof(m_squares)/sizeof(Square), Square());
    PieceFactory pf;
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
            Square curSquare = Square(currentColor, currentId, Chess::kSquareWidth * x, Chess::kSquareWidth * y);
            m_squares[index] = curSquare;
            currentId.second += 1;
            if (currentColor == Square::Color::Black)
            {
                currentColor = Square::Color::White;
            }
            else
            {
                currentColor = Square::Color::Black;
            }

            if (CheckColumns(y))
            {
               m_pieces.push_back(SpawnPiece(y, x));
               m_squares[index].SetPiece(m_pieces.back());
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
