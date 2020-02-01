#pragma once

//#include <SDL.h>
//#include <SDL_ttf.h>
#include <SDL.h>

#include <memory>
#include <unordered_map>
#include "Constants/ChessConstants.h"


struct SDL_Texture;

class SDLTextureManager

{
public:
    std::shared_ptr<SDL_Texture> GetTexture(Chess::Piece piece, Chess::Color color);

private:
    std::unordered_multimap<char, SDL_Texture*> m_textures;
    bool CreateTextures();

    static constexpr SDL_Color kBlack{ (Uint8)10, (Uint8)10, (Uint8)10, (Uint8)0 };
    static constexpr SDL_Color kWhite{ (Uint8)500, (Uint8)500, (Uint8)500, (Uint8)0 };
    static constexpr SDL_Rect kTextRect{ 0, 0, 75, 75 };
};

