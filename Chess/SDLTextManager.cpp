#include "SDLTextManager.h"
#include "Constants/Constants.h"


SDLTextManager::SDLTextManager(SDL_Renderer* pRenderer)
    :m_pFont(nullptr, TTF_CloseFont), m_pRenderer(pRenderer)
{
}

std::shared_ptr<SDL_Texture> SDLTextManager::GetTexture(Chess::Piece piece, Chess::Color color)
{
    auto iterator = m_textures.find((char)piece);
    if (iterator == m_textures.end()) 
    {
        SDL_Color pieceColor;
        if (color == Chess::Color::kBlack) 
        {
            pieceColor = kBlack;
        }
        else
        {
            pieceColor = kWhite;
        }
        std::unique_ptr<SDL_Surface> surface = std::make_unique<SDL_Surface>(TTF_RenderText_Solid(m_pFont.get(), (char*)piece, pieceColor));
        std::shared_ptr<SDL_Texture> texture = std::make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(m_pRenderer, surface.get()));
        m_textures.emplace((char)piece, texture);

        return texture;
    }
    //SDL_Renderer test;
    return iterator->second;
}

bool SDLTextManager::LoadFont()
{
    m_pFont.reset(TTF_OpenFont(kArialFilePath, kFontSize));
    if (m_pFont.get() == nullptr) 
    {
        return true;
    }
    return false;
}

std::shared_ptr<SDL_Texture> SDLTextManager::CreateTexture()
{
    return std::shared_ptr<SDL_Texture>();
}
