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

SDL_Texture* SDLTextureManager::GetTexture(char character)
{
    assert(!m_textures.empty());
    auto iterator = m_textures.find(character);
    if (iterator != m_textures.end())
    {
        return iterator->second;
    }

    return nullptr;
}

void SDLTextureManager::CreatePieceTexture(TTF_Font* pFont, Chess::Piece piece, char color, SDL_Renderer* pRenderer)
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
    char pieceArray[2] = { (char)piece, '\0' };
    SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, pieceArray, sdlColor);
    SDL_Texture* pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    m_textures.emplace((char)piece + color, pTex);
    SDL_FreeSurface(pSurface);
}

void SDLTextureManager::CreateCoordinateTexture(TTF_Font* pFont, char character, SDL_Renderer* pRenderer)
{
    SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, &character, kRed);
    SDL_Texture* pTex = SDL_CreateTextureFromSurface(pRenderer, pSurface);

    m_textures.emplace(character, pTex);
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

    CreatePieceTexture(font.get(), Chess::Piece::kPawn, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kPawn, (char)Chess::Color::kBlack, pRenderer);

    CreatePieceTexture(font.get(), Chess::Piece::kBishop, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kBishop, (char)Chess::Color::kBlack, pRenderer);

    CreatePieceTexture(font.get(), Chess::Piece::kKnight, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kKnight, (char)Chess::Color::kBlack, pRenderer);

    CreatePieceTexture(font.get(), Chess::Piece::kRook, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kRook, (char)Chess::Color::kBlack, pRenderer);

    CreatePieceTexture(font.get(), Chess::Piece::kQueen, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kQueen, (char)Chess::Color::kBlack, pRenderer);

    CreatePieceTexture(font.get(), Chess::Piece::kKing, (char)Chess::Color::kWhite, pRenderer);
    CreatePieceTexture(font.get(), Chess::Piece::kKing, (char)Chess::Color::kBlack, pRenderer);

    font.reset(TTF_OpenFont(kArialFilePath, kFontSize/2));

    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::a), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::b), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::c), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::d), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::e), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::f), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::g), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::h), pRenderer);

    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::one), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::two), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::three), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::four), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::five), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::six), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::seven), pRenderer);
    CreateCoordinateTexture(font.get(), static_cast<char>(Chess::Coordinate::eight), pRenderer);


    return true;
}
