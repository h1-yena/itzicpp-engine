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
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <assert.h>
#include "game.hpp"

Game::Game()
	: isRunning(false)
	, screenWidth(0)
	, screenHeight(0)
	, window(nullptr)
	, screenSurface(nullptr)
{}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::Initialize(int screenWidth, int screenHeight)
{
	assert(screenWidth > 0 || screenHeight > 0);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not be initialized! SDL_Error: "
							<< SDL_GetError() << std::endl;

		exit(1);
	}

	// Create window
	window = SDL_CreateWindow("ItziCpp Engine",
														SDL_WINDOWPOS_UNDEFINED,
														SDL_WINDOWPOS_UNDEFINED,
														screenWidth,
														screenHeight,
														SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Window could not be created! SDL_Error: "
							<< SDL_GetError() << std::endl;
		exit(1);
	}

	// Draw window screen surface
	screenSurface = SDL_GetWindowSurface(window);

	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	// Wait two seconds
	SDL_Delay(2000);

	std::cout << "Game Initialized" << std::endl;
	isRunning = true;
}

void Game::HandleInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ||
				event.key.keysym.scancode == SDL_SCANCODE_Q) {
			isRunning = false;
		}
		break;
	case SDL_KEYUP:
		break;
	default:
		break;
	}
}

void Game::Update()
{
	HandleInput();
	std::cout << "Game Updated" << std::endl;
}

void Game::Render()
{
	std::cout << "Game Rendered" << std::endl;
}

void Game::Terminate()
{
	// Destroy Window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	std::cout << "Game Terminated" << std::endl;
}

bool Game::IsRunning() const
{
	return isRunning;
}
