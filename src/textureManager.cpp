// =====================================================================================
//
//       Filename:  textureManager.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 05:57:14 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include "./textureManager.hpp"
#include "./game.hpp"
#include <SDL2/SDL_render.h>

TextureManager::TextureManager() {}

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::Draw(SDL_Renderer* renderer,
													SDL_Texture* texture,
													SDL_Rect sourceRect,
													SDL_Rect destRect,
													SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, &sourceRect, &destRect, 0.0f, NULL, flip);
}
