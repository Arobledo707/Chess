#pragma once
#include "../Interfaces/Board.h"
#include "ChessGameState.h"
#include "Square.h"
#include "../SDLTextureManager.h"

struct SDL_Renderer;

class ChessBoard : public Board
{
public:
    ChessBoard();
    // Inherited via Board
    virtual void Initialize(SDL_Renderer* pRenderer) override;
    virtual void StartGame() override;
    virtual const int GetCurrentPlayer() const override;
    virtual const int GetAvailableMoves() const override;
    virtual void MakeMove(unsigned int move) override;
    virtual int CheckForGameEnd() const override;
    virtual int PrintGameEnd() override;
    virtual void Render(SDL_Renderer* pRenderer) override;
    
private:
    void SpawnPieces();
    void SpawnPawns();
private:
    ChessGameState m_currentState;
    SDLTextureManager m_textureManager;
    std::unique_ptr<PieceFactory> m_pieceFactory;
    Piece* m_selectedPiece;
    Chess::Color m_currentTurn;

    std::vector<unsigned int> m_moves{};

    // Inherited via Board
    virtual const bool OnClick() override;

};

