#pragma once
#include <memory>
#include <vector>
#include "../Constants/ChessConstants.h"
struct SDL_Texture;
struct SDL_Renderer;
class Piece
{
public:
    Piece(std::shared_ptr<SDL_Texture> pTexture, Chess::Color color, unsigned int index) 
        : m_pTexture(pTexture), m_color(color), m_index(index) {};
    virtual void Move() = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual std::vector<unsigned int> GetAvailableMoves() = 0;
private:
    const Chess::Color m_color;
    std::shared_ptr<SDL_Texture> m_pTexture;
    unsigned int m_index;
    Chess::Piece m_type;
};

