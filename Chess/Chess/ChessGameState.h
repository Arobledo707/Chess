#pragma once
#include "Square.h"
#include "../Interfaces/Piece.h"
#include "../Constants/ChessConstants.h"
#include <memory>
#include <vector>
struct SDL_Renderer;
class ChessGameState
{
public:
    ChessGameState();
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer) const;

private:
    
    Square m_squares[Chess::kBoardSize];
    Square* m_blackSquares[Chess::kBoardWidth / 2];
    Square* m_whiteSquares[Chess::kBoardWidth / 2];
    std::vector<std::unique_ptr<Piece>> m_pieces;
};

