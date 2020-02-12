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
    void SpawnPieces(const SDLTextureManager& textureManager);
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer);
    void AddPiece(std::unique_ptr<Piece> piece, unsigned int i);
private:
    bool CheckColumns(int column);
    std::unique_ptr<Piece> SpawnPiece(int column, int row);
    void SpawnPawns(const SDLTextureManager& textureManager);

private:
    Square m_squares[Chess::kBoardSize];
    std::vector<std::unique_ptr<Piece>> m_pieces;
    std::unique_ptr<PieceFactory> m_pieceFactory;
};

