#include "SDLTextureManager.h"
#include "Constants/Constants.h"
//#include <SDL_ttf.h>
#include <cassert>
SDL_Texture* SDLTextureManager::GetTexture(Chess::Piece piece, Chess::Color color)
{
    //TODO just use ordered map and concatenate the chars for one KEY --- piece + color
    assert(!m_textures.empty());

    char texKey = (char)piece + (char)color;
    auto iterator = m_textures.find(texKey);
    if (iterator != m_textures.end())
    {
        return iterator->second;
    }

    return nullptr;
}

void SDLTextureManager::CreateTexture(TTF_Font* pFont, Chess::Piece piece, char color, SDL_Renderer* pRenderer)
{
    SDL_Color sdlColor;
    if (color == (char)Chess::Color::kBlack) 
    {
        sdlColor = kBlack;
    }
    else 
    {
        sdlColor = kWhite;
    }
    char pieceRef = (char)piece;
    SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, &pieceRef, sdlColor);
    SDL_Texture* pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)piece + color, pTex);
    SDL_FreeSurface(pSurface);
}

SDLTextureManager::SDLTextureManager()
{
}

SDLTextureManager::~SDLTextureManager()
{

}

bool SDLTextureManager::CreateTextures(SDL_Renderer* pRenderer)
{
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font(nullptr, TTF_CloseFont);
    font.reset(TTF_OpenFont(kArialFilePath, kFontSize));

    CreateTexture(font.get(), Chess::Piece::kPawn, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kPawn, (char)Chess::Color::kBlack, pRenderer);

    CreateTexture(font.get(), Chess::Piece::kBishop, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kBishop, (char)Chess::Color::kBlack, pRenderer);

    CreateTexture(font.get(), Chess::Piece::kKnight, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kKnight, (char)Chess::Color::kBlack, pRenderer);

    CreateTexture(font.get(), Chess::Piece::kRook, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kRook, (char)Chess::Color::kBlack, pRenderer);

    CreateTexture(font.get(), Chess::Piece::kQueen, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kQueen, (char)Chess::Color::kBlack, pRenderer);

    CreateTexture(font.get(), Chess::Piece::kKing, (char)Chess::Color::kWhite, pRenderer);
    CreateTexture(font.get(), Chess::Piece::kKing, (char)Chess::Color::kBlack, pRenderer);


    return true;
}
