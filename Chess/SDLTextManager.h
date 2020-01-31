#pragma once
#include <memory>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Constants/ChessConstants.h"
class SDLTextManager
{
public:
    SDLTextManager();
private:
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_pFont;
    std::unordered_map<Chess::Piece, std::shared_ptr<SDL_Texture>> m_Textures;
};

