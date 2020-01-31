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
    void Render(SDL_Renderer* pRenderer) const;
    void SetColor(Color color);
    void SetPiece(std::shared_ptr<Piece> piece);

private:
    Color m_color;
    std::weak_ptr<Piece> m_pPiece;
    std::pair<char, int> m_Id;
    SDL_Rect m_rect; 
};

