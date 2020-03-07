#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <unordered_map>
#include "Constants/ChessConstants.h"

//////////DSASGLEFJSLFLSKDFJLFJDSLFJDSLKFJLFJDSLF
class SDLTextManager
{
public:
    SDLTextManager(SDL_Renderer* pRenderer);
    std::shared_ptr<SDL_Texture> GetTexture(Chess::Piece piece, Chess::Color color);
private:
    SDL_Renderer* m_pRenderer;

    bool LoadFont();
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_pFont;
    std::unordered_map<char, std::shared_ptr<SDL_Texture>> m_textures;
};

