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
    ChessBoard(const ChessBoard& board);
    ChessBoard& operator=(const ChessBoard& board);

    // Inherited via Board
    virtual void Initialize(SDL_Renderer* pRenderer) override;
    virtual int StartGame() override;
    virtual const int GetCurrentPlayer() const override;
    virtual const Moves GetAvailableMoves() override;
    virtual void MakeMove(Move) override;
    virtual int CheckForGameEnd() const override;
    virtual int PrintGameEnd() override;
    virtual void Render(SDL_Renderer* pRenderer) override;
    virtual Board* CloneSelf() const override;
    virtual const bool OnClick() override;

    
private:
    // Inherited via Board
    virtual const int GetPlayerColor() const override;
    virtual void AlternateTurns() override;

    void PromotePawn();
    void SpawnPieces();
    void SpawnPawns();
    void SpawnNonPawns(Chess::Color color, int maxIndex, int lowIndex);
    int AssignRoles();
private:
    ChessGameState m_currentState;
    SDLTextureManager m_textureManager;
    PieceFactory m_pieceFactory;
    Piece* m_selectedPiece;
    Chess::Color m_currentTurn = Chess::Color::kWhite;
    Chess::Color m_playerColor;
    Moves m_moves{};
    Moves m_pastMoves{};

};

