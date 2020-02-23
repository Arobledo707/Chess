#pragma once
#include "../Interfaces/Piece.h"
#include <memory>
#include <SDL.h>

class Square
{
public:
    enum class Color 
    {
        White = 1,
        Black = 2
    };

public:
    Square();
    Square(Color color, std::pair<char, int> id, int xPos, int yPos);
    Square operator=(Square other);
    
    void Render(SDL_Renderer* pRenderer) const;
    void SetColor(Color color);
    void SetPiece(Piece* piece);
    Piece* GetPiece() { return m_pPiece; }
    const SDL_Rect& GetRect() { return m_rect; };

private:
    Color m_color;
    Piece* m_pPiece = nullptr;
    std::pair<char, int> m_Id;
    SDL_Rect m_rect; 
};

