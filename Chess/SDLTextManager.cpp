#include "SDLTextManager.h"
#include "Constants/Constants.h"


SDLTextManager::SDLTextManager(SDL_Renderer* pRenderer)
    :m_pFont(nullptr, TTF_CloseFont), m_pRenderer(pRenderer)
{
}

//TODO SDL_freesurface
// unique_ptr sdl surface

std::shared_ptr<SDL_Texture> SDLTextManager::GetTexture(Chess::Piece piece, Chess::Color color)
{
    auto iterator = m_textures.find((char)piece);
    if (iterator == m_textures.end()) 
    {
        SDL_Color pieceColor;
        if (color == Chess::Color::kBlack) 
        {
            pieceColor = Chess::kBlackPiece;
        }
        else
        {
            pieceColor = Chess::kWhitePiece;
        }

    //    //this?????????????????????????????????
    //    //std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface = std::make_unique<SDL_Surface, decltype(&SDL_FreeSurface)>(TTF_RenderText_Solid(m_pFont.get(), (char*)piece, pieceColor), SDL_FreeSurface);
    //    //.reset(std::make_unique<SDL_Surface>(TTF_RenderText_Solid(m_pFont.get(), (char*)piece, pieceColor)).get());
    //    //std::shared_ptr<SDL_Texture> texture = std::make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(m_pRenderer, surface.get()));
    //    //m_textures.emplace((char)piece, texture);

    //    SDL_Surface* pSurface = TTF_RenderText_Solid(m_pFont.get(), (char*)piece, pieceColor);
    //    std::shared_ptr<SDL_Texture> texture = std::make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(m_pRenderer, pSurface));
    //    SDL_FreeSurface(pSurface);
    //    //todo delete pSurface
    //    return texture;

    }
    return iterator->second;
    //return std::shared_ptr<SDL_Texture>();
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

