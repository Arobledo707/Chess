#include "SDLTextureManager.h"
#include "Constants/Constants.h"
#include <SDL_ttf.h>
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

SDLTextureManager::SDLTextureManager()
{
}

SDLTextureManager::~SDLTextureManager()
{
}

//TODO refactor this and have it call a function(piece, color)
bool SDLTextureManager::CreateTextures(SDL_Renderer* pRenderer)
{
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font (nullptr, TTF_CloseFont);
    font.reset(TTF_OpenFont(kArialFilePath, kFontSize));

    SDL_Surface* pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kPawn, kWhite);
    SDL_Texture* pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kPawn + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kPawn, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kPawn + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kBishop, kWhite);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kBishop + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kBishop, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kBishop + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kKnight, kWhite);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kKnight + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kKnight, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kKnight + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kRook, kWhite);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kRook + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kRook, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kRook + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kQueen, kWhite);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kQueen + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kQueen, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kQueen + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kKing, kWhite);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kKing + (char)Chess::Color::kWhite, pTex);
    SDL_FreeSurface(pSurface);

    pSurface = TTF_RenderText_Solid(font.get(), (const char*)Chess::Piece::kKing, kBlack);
    pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)Chess::Piece::kKing + (char)Chess::Color::kBlack, pTex);
    SDL_FreeSurface(pSurface);




    return true;
}
