#include "Pawn.h"


Pawn::Pawn(SDL_Texture* pTexture, Chess::Color color, unsigned int index)
    :Piece(pTexture, color, index)
{
}

void Pawn::Move()
{
}

void Pawn::Render(SDL_Renderer* pRenderer)
{
    //if (GetColor() == Chess::Color::kWhite) 
    //{
    //    
    //}
    //SDL_RenderCopy(pRenderer, GetTexture(), NULL, GetRect());
}

std::vector<unsigned int> Pawn::GetAvailableMoves()
{
    return std::vector<unsigned int>();
}
