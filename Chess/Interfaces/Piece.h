#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include "../Constants/ChessConstants.h"

class Piece
{
public:
    Piece(SDL_Texture* pTexture, Chess::Color color, unsigned int index) 
        : m_pTexture(pTexture), m_color(color), m_index(index), m_type(Chess::Piece::kInvalid)
    {
        m_rect.x = (index % Chess::kBoardWidth) * Chess::kSquareWidth;
        m_rect.y = (index / Chess::kBoardWidth) * Chess::kSquareWidth;
    };
    virtual void Move() = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual std::vector<unsigned int> GetAvailableMoves() = 0;
    const Chess::Color GetColor() { return m_color; }
    SDL_Texture* GetTexture() const { return m_pTexture; }

protected:
    void SetPosition(unsigned int x, unsigned int y) { m_rect.x = x; m_rect.y = y; };
    SDL_Rect GetRect() const { return m_rect; }
private:
    const Chess::Color m_color;
    SDL_Texture* m_pTexture;
    unsigned int m_index;
    Chess::Piece m_type;
    SDL_Rect m_rect { 0, 0, Chess::kSquareWidth, Chess::kSquareWidth};
};

