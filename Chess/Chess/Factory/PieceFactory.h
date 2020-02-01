#pragma once
#include "../../Constants/ChessConstants.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Queen.h"
#include "../Pieces/King.h"
#include <memory>
#include <cassert>
#include <iostream>

struct SDL_Texture;

class PieceFactory
{
public:
    template<Chess::Piece T, typename U>
    std::unique_ptr<U>ReturnChessPiece(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index) 
    {
        assert(T != Chess::Piece::kInvalid);
        std::unique_ptr<U> pChessPiece;
        switch (T)
        {
        case Chess::Piece::kPawn:
            pChessPiece = std::make_unique<Pawn>(pTexture, color, index);
            break;
        case Chess::Piece::kKnight:
            pChessPiece = std::make_unique<Knight>(pTexture, color, index);
            break;
        case Chess::Piece::kBishop:
            pChessPiece = std::make_unique<Bishop>(pTexture, color, index);
            break;
        case Chess::Piece::kRook:
            pChessPiece = std::make_unique<Rook>(pTexture, color, index);
            break;
        case Chess::Piece::kQueen:
            pChessPiece = std::make_unique<Queen>(pTexture, color, index);
            break;
        case Chess::Piece::kKing:
            pChessPiece = std::make_unique<King>(pTexture, color, index);
            break;
        case Chess::Piece::kInvalid:
        default:
            std::cout << "Error: invalid piece type in PieceFactory" << std::endl;
        }
        return pChessPiece;
    }

    template<typename T>
    std::shared_ptr<T>ReturnPiece(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    {
        std::shared_ptr<T> piece = std::make_shared<T>(pTexture, color, index);
        return piece;
    }


};

