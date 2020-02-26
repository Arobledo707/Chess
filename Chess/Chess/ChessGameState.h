#pragma once
#include "Square.h"
#include "../Interfaces/Piece.h"
#include "../Constants/ChessConstants.h"
#include "Factory/PieceFactory.h"
#include "../SDLTextureManager.h"
#include <memory>
#include <vector>

//TODO call delete
struct SDL_Renderer;
class ChessGameState
{
public:
    ChessGameState();
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer);
    void AddPiece(std::unique_ptr<Piece> piece, unsigned int i);
    Square& GetSquare(unsigned int index);
    void RemovePiece(Piece* pPiece);
    void AddPiece();
    King* GetWhiteKing() const { return m_pWhiteKing; }
    King* GetBlackKing() const { return m_pBlackKing; }

private:
    Square m_squares[Chess::kBoardSize];
    std::vector<std::unique_ptr<Piece>> m_pieces;
    std::unique_ptr<PieceFactory> m_pieceFactory;
    King* m_pWhiteKing = nullptr;
    King* m_pBlackKing = nullptr;
};