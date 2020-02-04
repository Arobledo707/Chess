#pragma once
#include "Square.h"
#include "../Interfaces/Piece.h"
#include "../Constants/ChessConstants.h"
#include "Factory/PieceFactory.h"
#include "../SDLTextureManager.h"
#include <memory>
#include <vector>
struct SDL_Renderer;
class ChessGameState
{
public:
    ChessGameState();
    void SpawnPieces();
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer);
private:
    bool CheckColumns(int column);
    std::unique_ptr<Piece> SpawnPawn(Chess::Color color, unsigned int index);
    std::unique_ptr<Piece> SpawnPiece(int column, int row);
    void SpawnPawns();

private:
    Square m_squares[Chess::kBoardSize];
    std::vector<std::unique_ptr<Piece>> m_pieces;
    std::unique_ptr<PieceFactory> m_pieceFactory;
    SDLTextureManager m_textureManager;
};

