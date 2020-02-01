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
    void SpawnPieces();
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer) const;
private:
    bool CheckColumns(int column);
    std::shared_ptr<Piece> SpawnPawn(Chess::Color color, unsigned int index);
    std::shared_ptr<Piece> SpawnPiece(int column, int row);
    void SpawnPawns();

private:
    Square m_squares[Chess::kBoardSize];
    std::vector<std::shared_ptr<Piece>> m_pieces;
    std::unique_ptr<PieceFactory> m_pieceFactory;
};

