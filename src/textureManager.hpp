// =====================================================================================
//
//       Filename:  textureManager.hpp
//
//    Description:  Manages all resources in game (textures, sounds, etc).
//
//        Version:  1.0
//        Created:  06/20/2020 05:54:16 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <SDL2/SDL.h>

class TextureManager
{
private:
	TextureManager();
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
	static void Draw(SDL_Renderer* renderer,
									 SDL_Texture* texture,
									 SDL_Rect sourceRect,
									 SDL_Rect destRect,
									 SDL_RendererFlip flip);
};
