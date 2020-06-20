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
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <assert.h>
#include "game.hpp"

Game::Game()
	: isRunning(false)
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

void Game::Initialize(int screenWidth, int screenHeight)
{
	// End program if screensize is incorrect.
	assert(screenWidth > 0 || screenHeight > 0);
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

	std::cout << "Game Initialized" << std::endl;
	isRunning = true;
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
	HandleInput();
	std::cout << "Game Updated" << std::endl;
}

void Game::Render()
{
	// Draw background
	SDL_SetRenderDrawColor(renderer, 40, 42, 54, 255);
	SDL_RenderClear(renderer);

	// Draw test rect
	static SDL_Rect rect {
		screenWidth / 2,
		screenHeight / 2,
		100,
		100
	};

	static int xVel = 1;
	static int yVel = 1;

	rect.x += xVel;
	rect.y += yVel;

	if (rect.x >= (screenWidth - rect.w) || rect.x <= 0) {
		xVel *= -1;
	}
	if (rect.y >= (screenHeight - rect.h) || rect.y <= 0) {
		yVel *= -1;
	}

	SDL_SetRenderDrawColor(renderer, 255, 121, 198, 255);
	SDL_RenderFillRect(renderer, &rect);

	// Swap buffers
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

bool Game::IsRunning() const
{
	return isRunning;
}
