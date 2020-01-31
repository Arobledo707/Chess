#pragma once
#include "Square.h"
#include "../Interfaces/Piece.h"
#include "../Constants/ChessConstants.h"
#include "Factory/PieceFactory.h"
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
    bool CheckColumns(int column);
    void SpawnPawn(Chess::Color color, unsigned int index);
    std::shared_ptr<Piece> SpawnPiece(int column, int row);

private:
    
    Square m_squares[Chess::kBoardSize];
    Square* m_blackSquares[Chess::kBoardWidth / 2];
    Square* m_whiteSquares[Chess::kBoardWidth / 2];
    std::vector<std::shared_ptr<Piece>> m_pieces;
    std::unique_ptr<PieceFactory> m_pieceFactory;
};

