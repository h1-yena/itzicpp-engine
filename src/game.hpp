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
#include <SDL2/SDL.h>

class Game
{
private:
	// Force Singleton
	Game();

	// Game attributes
	bool isRunning;

	// Screen parameters
	int screenWidth;
	int screenHeight;

	// SDL Rendering attributes
	SDL_Window* window;
	SDL_Surface* screenSurface;

	// Game Logic
	void HandleInput();

public:
	// Obtain Singleton
	static Game& GetInstance();

	// Game logic
	void Initialize(int screenWidth, int screenHeight);
	void Update();
	void Render();
	void Terminate();

	bool IsRunning() const;
};
