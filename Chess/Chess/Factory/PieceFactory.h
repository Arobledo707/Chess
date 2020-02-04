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

    template<typename T>
    std::unique_ptr<T>ReturnPiece(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    {
        std::unique_ptr<T> piece = std::make_unique<T>(pTexture, color, index);
        return piece;
    }

};

