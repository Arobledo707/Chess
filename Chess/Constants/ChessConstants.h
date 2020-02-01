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
    static constexpr unsigned int kBlackPieceColumnn = 7;
    static constexpr unsigned int kWhitePieceColumn = 0;

    enum class Color : char 
    {
        kWhite = 1,
        kBlack = 2,
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


