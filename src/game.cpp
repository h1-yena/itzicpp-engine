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
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <glm/glm.hpp>
#include <iostream>
#include "./constants.hpp"
#include "./entityManager.hpp"
#include "./game.hpp"
#include "entity.hpp"

glm::vec2 pos = glm::vec2(100.0f, 100.0f);
glm::vec2 vel = glm::vec2(300.0f, 300.0f);
int rectW = 150.0f;
int rectH = 150.0f;

Game::Game()
	: isRunning(false)
	, entityManager(EntityManager::GetInstance())
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

	isRunning = true;

	std::cout << "Game Initialized" << std::endl;
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
	static int ticksLastFrame = 0;

	// Wait until 16.6ms (or 60fps) since last frame.
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	// Delta time is the difference in ticks from last frame converted to seconds.
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// Clamp deltaTime to a minimum value.
	deltaTime = (deltaTime > 0.05) ? 0.05f : deltaTime;

	// Sets the new ticcks for the current frame to be used in the next pass.
	ticksLastFrame = SDL_GetTicks();

	// NOTE: Debug triangle.
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;

	// Clamp debug triangle to screen width.
	if (pos.x >= (screenWidth - rectW) || pos.x <= 0) {
		vel.x *= -1;
	}
	if (pos.y >= (screenHeight - rectH) || pos.y <= 0) {
		vel.y *= -1;
	}

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

	// 2. Draw all game objects
	// Draw test rect
	SDL_Rect rect {
		(int)pos.x,
		(int)pos.y,
		rectW,
		rectH
	};

	// Draw rectangle
	SDL_SetRenderDrawColor(renderer, 255, 121, 198, 255);
	SDL_RenderFillRect(renderer, &rect);

	entityManager.Render();

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

bool Game::IsRunning() const
{
	return isRunning;
}
