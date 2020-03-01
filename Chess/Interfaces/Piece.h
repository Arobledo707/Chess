#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include "../Constants/ChessConstants.h"
#include "../Constants/Constants.h"
struct ChessGameState;

class Piece
{
public:
    Piece(SDL_Texture* pTexture, Chess::Color color, unsigned int index, Chess::Piece type = Chess::Piece::kInvalid)
        : m_pTexture(pTexture), m_color(color), m_index(index), m_type(type)
    {
        m_rect.x = (index % Chess::kBoardWidth) * Chess::kSquareWidth;
        m_rect.y = (index / Chess::kBoardWidth) * Chess::kSquareWidth;
    };

    Piece(const Piece& piece);
    Piece& operator=(const Piece& piece);

    virtual void Move(unsigned int move);
    void Render(SDL_Renderer* pRenderer) { SDL_RenderCopy(pRenderer, GetTexture(), NULL, &GetRect()); }
    virtual Moves GetAvailableMoves(ChessGameState* pGameState) = 0;
    const Chess::Color GetColor() { return m_color; }
    SDL_Texture* GetTexture() const { return m_pTexture; }
    unsigned int GetIndex() const { return m_index; }
    Chess::Piece GetType() const { return m_type; }
    bool HasMoved() { return m_hasMoved; }
    void SetMoved() { m_hasMoved = true; }
    void CanCheck(Piece* pPiece);

protected:
    void SetPosition(unsigned int x, unsigned int y) { m_rect.x = x; m_rect.y = y; };
    SDL_Rect GetRect() const { return m_rect; }
    void AddMoveIfValid(unsigned int index, Moves& moves, ChessGameState* pGameState);
    unsigned int m_index;

private:
    const Chess::Color m_color;
    SDL_Texture* m_pTexture;
    Chess::Piece m_type;
    SDL_Rect m_rect { 0, 0, Chess::kSquareWidth, Chess::kSquareWidth};
    bool m_hasMoved = false;
};

