#include "Square.h"

Square::Square()
{
}

Square::Square(Color color, std::pair<char, int> id, int xPos, int yPos)
    :m_color(color), m_Id(id)
{
    m_rect.x = xPos;
    m_rect.y = yPos;
    m_rect.h = 75;
    m_rect.w = 75;
}

Square Square::operator=(Square other)
{
    m_color = other.m_color;
    m_pPiece = other.m_pPiece;
    m_Id = other.m_Id;
    m_rect = other.m_rect;
    return *this;
}

void Square::Render(SDL_Renderer* pRenderer) const
{
    if (m_color == Color::Black)
    {
        SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 100);
    }
    else 
    {
        SDL_SetRenderDrawColor(pRenderer, 100, 100, 100, 10);
    }
    SDL_RenderFillRect(pRenderer, &m_rect);

}

void Square::SetColor(Color color)
{
    m_color = color;
}

void Square::SetPiece(Piece* piece)
{
    m_pPiece = piece;
}
