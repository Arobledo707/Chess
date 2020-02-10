#pragma once

//#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL.h>

#include <memory>
#include <unordered_map>
#include "Constants/ChessConstants.h"


struct SDL_Texture;
struct SDL_Renderer;

class SDLTextureManager

{
public:
    SDLTextureManager();
    ~SDLTextureManager();
    bool CreateTextures(SDL_Renderer* pRenderer);

    SDL_Texture* GetTexture(Chess::Piece piece, Chess::Color color);
private:
    void CreateTexture(TTF_Font* pFont, Chess::Piece piece, char color, SDL_Renderer* pRenderer);
private:
    std::unordered_map<char, SDL_Texture*> m_textures;
    static constexpr SDL_Color kBlack{ (Uint8)10, (Uint8)10, (Uint8)10, (Uint8)0 };
    static constexpr SDL_Color kWhite{ (Uint8)500, (Uint8)500, (Uint8)500, (Uint8)0 };
    static constexpr SDL_Rect kTextRect{ 0, 0, 75, 75 };
};

