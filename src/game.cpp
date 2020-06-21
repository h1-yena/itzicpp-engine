// =====================================================================================
//
//       Filename:  game.cpp
//
//    Description:  Implementation of Game Singleton.
//
//        Version:  1.0
//        Created:  06/16/2020 06:24:03 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

#include "./game.hpp"
#include "./constants.hpp"
#include "./components/transformComponent.hpp"
#include "./components/spriteComponent.hpp"
#include "./assetManager.hpp"
#include "./entityManager.hpp"

Game::Game()
	: isRunning(false)
	, entityManager(EntityManager::GetInstance())
	, assetManager(AssetManager::GetInstance())
	, screenWidth(0)
	, screenHeight(0)
	, window(nullptr)
	, renderer(nullptr)
{}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::Initialize(unsigned int screenWidth, unsigned int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	// Initialize SDL, exit if failed.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL could not be initialized! SDL_Error: "
							<< SDL_GetError() << std::endl;

		exit(1);
	}

	// Create window, exit if failed.
	window = SDL_CreateWindow(
						 "ItziCpp Engine",
						 SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED,
						 screenWidth,
						 screenHeight,
						 SDL_WINDOW_SHOWN
					 );
	if (!window) {
		std::cerr << "SDL Window could not be created! SDL_Error: "
							<< SDL_GetError() << std::endl;
		exit(1);
	}

	// Create renderer, exit if failed.
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "SDL Renderer could not be created! SDL_Error: "
							<< SDL_GetError() << std::endl;
		exit(1);
	}

	LoadLevel(0);

	isRunning = true;

	std::cout << "Game Initialized" << std::endl;
}

void Game::LoadLevel(int levelNum)
{
	// 1. Load Assets
	std::string textureFilePath = "./assets/images/jungle/tank-big-right.png";
	assetManager.AddTexture("tank-image", textureFilePath.c_str(), renderer);

	// 2. Load Entities
	Entity& tank = entityManager.AddEntity("tank");
	tank.AddComponent<TransformComponent>(300, 300, 20, 20, 1, 1, 32, 32);
	tank.AddComponent<SpriteComponent>("tank-image");
}

void Game::HandleInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT: {
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN: {
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ||
				event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
		break;
	}
	case SDL_KEYUP: {
		break;
	}
	default:
		break;
	}
}

void Game::Update()
{
	// Time-step variables.
	static unsigned int ticksLastFrame = 0;

	// Wait until 16.6ms (or 60fps) since last frame.
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && (unsigned int)timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	// Delta time is the difference in ticks from last frame converted to seconds.
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a minimum value.
	deltaTime = (deltaTime > 0.05) ? 0.05f : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass.
	ticksLastFrame = SDL_GetTicks();

	// Tell entity manager to update all entities
	entityManager.Update(deltaTime);

	HandleInput();
	std::cout << "Game Updated" << std::endl;
}

void Game::Render()
{
	// 0. Set background color
	SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);

	// 1. Clear back buffer
	SDL_RenderClear(renderer);

	if (entityManager.HasNoEntities()) {
		return;
	}

	// 2. Draw all game objects
	entityManager.Render(renderer);

	// 3. Swap front and back buffers
	SDL_RenderPresent(renderer);

	std::cout << "Game Rendered" << std::endl;
}

void Game::Destroy()
{
	// Destroy Window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	std::cout << "Game Terminated" << std::endl;
}

SDL_Renderer* Game::GetRenderer() const
{
	return renderer;
}

bool Game::IsRunning() const
{
	return isRunning;
}
