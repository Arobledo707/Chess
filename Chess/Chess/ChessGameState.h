#pragma once
#include "Square.h"
#include "../Constants/ChessConstants.h"
#include "../SDLTextureManager.h"
#include <memory>
#include <vector>

//struct Piece;
struct SDL_Renderer;

class ChessGameState
{
public:
    ChessGameState();
    ~ChessGameState();
    ChessGameState(const ChessGameState& state);
    ChessGameState& operator=(const ChessGameState& state);

    void Copy(const ChessGameState& cgs);
    void ResetBoard();
    void Render(SDL_Renderer* pRenderer);
    void AddPiece(Piece* piece, unsigned int i);
    Square& GetSquare(unsigned int index);
    void RemovePiece(Piece* pPiece);
    void ReplacePiece(Piece* pPiece, Chess::Piece type, SDLTextureManager* pTexManager);
    Piece* GetWhiteKing() const { return m_pWhiteKing; }
    Piece* GetBlackKing() const { return m_pBlackKing; }
    std::vector<Piece*>& GetPieces() { return m_pieces; }
private:
    Square m_squares[Chess::kBoardSize];
    std::vector<Piece*> m_pieces;
    Piece* m_pWhiteKing = nullptr;
    Piece* m_pBlackKing = nullptr;
};