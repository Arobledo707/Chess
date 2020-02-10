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
    SpawnPawns(textureManager);
}

void ChessGameState::Render(SDL_Renderer* pRenderer)
{
    //static bool texturesCreated = false; 
    //if (!texturesCreated) 
    //{
    //    m_textureManager.CreateTextures(pRenderer);
    //    texturesCreated = true;
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

/*std::unique_ptr<Piece> ChessGameState::SpawnPawn(Chess::Color color, unsigned int index)
{
    return m_pieceFactory.get()->ReturnPiece<Pawn>(m_textureManager.GetTexture(Chess::Piece::kPawn, color), color, index);
} */  

//std::unique_ptr<Piece> ChessGameState::SpawnPiece(int column, int row)
//{
//    std::unique_ptr<Piece> piece;
//    if (column == Chess::kBlackPawnColumn) 
//    {
//        piece.reset(SpawnPawn(Chess::Color::kBlack, (column * Chess::kBoardWidth) + row).get());
//    }
//
//    else if(column == Chess::kWhitePawnColumn) 
//    {
//        piece.reset(SpawnPawn(Chess::Color::kWhite, (column * Chess::kBoardWidth) + row).get());
//
//    }
//    else if (column == Chess::kBlackPieceColumnn) 
//    {
//
//    }
//    else if (column == Chess::kWhitePieceColumn) 
//    {
//
//    }
//
//    return piece;
//}

void ChessGameState::SpawnPawns(const SDLTextureManager& textureManager)
{
    //TODO interate through half and instantiate 2 pawns at once?
    //spawn white pawns
    unsigned int whitePawnIndexEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kWhitePawnColumn * Chess::kBoardWidth); i < whitePawnIndexEnd; ++i) 
    {        
        m_pieces.push_back(m_pieceFactory.get()->ReturnPiece<Pawn>(nullptr, Chess::Color::kWhite, i));
        m_squares[i].SetPiece(m_pieces.back().get());
    }

    unsigned int blackPawnIndexEnd = (Chess::kBlackPawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;
    for (unsigned int i = (Chess::kBlackPawnColumn * Chess::kBoardWidth); i < blackPawnIndexEnd; ++i)
    {
        m_pieces.push_back(m_pieceFactory.get()->ReturnPiece<Pawn>(nullptr, Chess::Color::kBlack, i));
        m_squares[i].SetPiece(m_pieces.back().get());
    }

    unsigned int whitePawnPiecesEnd = (Chess::kWhitePawnColumn * Chess::kBoardWidth) + Chess::kBoardWidth;

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
