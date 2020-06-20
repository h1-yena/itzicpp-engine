// =====================================================================================
//
//       Filename:  game.hpp
//
//    Description:  Header file for main Game Singleton.
//
//        Version:  1.0
//        Created:  06/16/2020 06:22:02 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./entity.hpp"
#include "./components/component.hpp"

class EntityManager;
class AssetManager;

class Game
{
private:
	// Force Singleton
	Game();

	// Game attributes
	bool isRunning;

	// Managers
	EntityManager& entityManager;
	AssetManager& assetManager;

	// Screen parameters
	int screenWidth;
	int screenHeight;

	// SDL Rendering attributes
	SDL_Window*  window;
	SDL_Renderer* renderer;

	// Game Logic
	void HandleInput();

public:
	// Obtain Singleton
	static Game& GetInstance();

	// Game logic
	void Initialize(unsigned int screenWidth, unsigned int screenHeight);
	void Update();
	void Render();
	void Destroy();
	void LoadLevel(int levelNum);

	// Getters
	SDL_Renderer* GetRenderer() const;
	bool IsRunning() const;
};
