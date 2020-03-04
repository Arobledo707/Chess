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
    T* ReturnPiece(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    {
        T* piece = new T(pTexture, color, index);
        return piece;
    }

};

