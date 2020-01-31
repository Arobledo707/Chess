#include "ChessGameState.h"
#include <algorithm>
#include <iostream>
#include <SDL.h>
#include "../Chess/Factory/PieceFactory.h"
#include "../Chess/Pieces/Pawn.h"

ChessGameState::ChessGameState()
{
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
            //m_squares[(y * kBoardWidth) + x].SetColor(currentColor);
            Square curSquare = Square(currentColor, currentId, Chess::kSquareWidth * x, Chess::kSquareWidth * y);
            m_squares[index] = curSquare;//Square(currentColor, currentId, kSquareWidth, + kSquareWidth);
            currentId.second += 1;
            if (currentColor == Square::Color::Black)
            {
                //m_blackSquares[blackSquareCounter] = &m_squares[(y * kBoardWidth) + x];
               // ++blackSquareCounter;
                currentColor = Square::Color::White;
            }
            else
            {
                //m_whiteSquares[whiteSquareCounter] = &curSquare;
                //++whiteSquareCounter;
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
