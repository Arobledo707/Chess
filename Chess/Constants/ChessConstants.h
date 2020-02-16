#pragma once
//ChessConstants.h

namespace Chess
{
    static constexpr unsigned int kSquareWidth = 75;
    static constexpr unsigned int kBoardHeight = 8;
    static constexpr unsigned int kBoardWidth = 8;
    static constexpr size_t kBoardSize = kBoardHeight * kBoardWidth;
    static constexpr unsigned int kChessPieces = 32;
    static constexpr unsigned int kBlackPawnColumn = 6;
    static constexpr unsigned int kWhitePawnColumn = 1;
    static constexpr unsigned int kWhitePieceRow = 0;
    static constexpr unsigned int kBlackPieceRow = 7;

    enum class Color : char 
    {
        kWhite = 'W',
        kBlack = 'B',
    };

    enum class Piece : char 
    {
        kPawn = 'P',
        kKnight = 'N',
        kBishop = 'B',
        kRook = 'R',
        kQueen = 'Q',
        kKing = 'K',
        kInvalid = 'I'
    };
};


