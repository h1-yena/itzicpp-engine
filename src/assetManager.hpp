// =====================================================================================
//
//       Filename:  assetManager.hpp
//
//    Description:  Manages all the resources (let it be textures, sounds, animations).
//
//        Version:  1.0
//        Created:  06/20/2020 06:06:32 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>

#include "./entityManager.hpp"

class AssetManager
{
private:
	// Singleton
	AssetManager();

	EntityManager& entityManager;
	std::map<std::string, SDL_Texture*> textures;

public:
	static AssetManager& GetInstance();

	void ClearData();
	void AddTexture(std::string textureId, const char* filePath, SDL_Renderer* renderer);
	SDL_Texture* GetTexture(std::string textureId);

	~AssetManager();
};
