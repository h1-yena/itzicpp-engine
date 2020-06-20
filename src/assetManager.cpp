// =====================================================================================
//
//       Filename:  assetManager.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 06:09:07 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include "./assetManager.hpp"
#include "./textureManager.hpp"
#include <fstream>
#include <iostream>

AssetManager::AssetManager()
	: entityManager(EntityManager::GetInstance())
{}

AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

void AssetManager::ClearData()
{
	textures.clear();
}

void AssetManager::AddTexture(std::string textureId,
															const char* filePath,
															SDL_Renderer* renderer)
{
	// Check if filePath exists, return if not.
	std::ifstream f(filePath);
	if (!f.good()) {
		std::cerr << filePath << " couldn't be loaded" << std::endl;
		exit(1);
	}

	// Load and store if exists.
	textures.emplace(textureId, TextureManager::LoadTexture(filePath, renderer));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId)
{
	return textures[textureId];
}

AssetManager::~AssetManager()
{
	ClearData();
}
