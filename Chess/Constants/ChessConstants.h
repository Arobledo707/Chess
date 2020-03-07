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
    static constexpr unsigned int kLeftSideRemainder = 0;
    static constexpr unsigned int kRightSideRemainder = 7;

    enum class Color : char
    {
        kWhite = 'W',
        kBlack = 'B',
    };

    constexpr SDL_Color kBlackSquare { 200, 200, 200, 255 };
    constexpr SDL_Color kWhiteSquare { 100, 100, 100, 255 };
    constexpr SDL_Color kPurple { 150, 0, 150, 128 };
    constexpr SDL_Color kBlackPiece { 10, 10, 10, 0 };
    constexpr SDL_Color kWhitePiece { 500, 500, 500, 0 };

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

    static bool IsValidIndex(int index) {
        return index >= 0 && index <= (Chess::kBoardSize - 1);
    }
};


