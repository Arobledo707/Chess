#include "Square.h"
#include "../Constants/ChessConstants.h"

Square::Square()
{
}

Square::Square(Color color, std::pair<char, int> id, int xPos, int yPos)
    :m_color(color), m_Id(id)
{
    m_rect.x = xPos;
    m_rect.y = yPos;
    m_rect.h = Chess::kSquareWidth;
    m_rect.w = Chess::kSquareWidth;
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
        SDL_SetRenderDrawColor(pRenderer, Chess::kBlackSquare.r, Chess::kBlackSquare.g, Chess::kBlackSquare.b, Chess::kBlackSquare.a);
    }
    else 
    {
        SDL_SetRenderDrawColor(pRenderer, Chess::kWhiteSquare.r, Chess::kWhiteSquare.g, Chess::kWhiteSquare.b, Chess::kWhiteSquare.a);
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
