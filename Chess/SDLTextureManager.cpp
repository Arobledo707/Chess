#include "SDLTextureManager.h"

#include <SDL_ttf.h>
#include <cassert>
std::shared_ptr<SDL_Texture> SDLTextureManager::GetTexture(Chess::Piece piece, Chess::Color color)
{
    //TODO just use ordered map and concatenate the chars for one KEY --- piece + color
    assert(!m_textures.empty());

    SDL_Color pieceColor;
    if (color == Chess::Color::kBlack)
    {
        pieceColor = kBlack;
    }
    else
    {
        pieceColor = kWhite;
    }

    auto iterator = m_textures.equal_range((char)piece);


    for (auto iter = iterator.first; iter != iterator.second; ++iter) 
    {
        //if(iter->second)
    }

    return std::shared_ptr<SDL_Texture>();
}

bool SDLTextureManager::CreateTextures()
{


    return false;
}
