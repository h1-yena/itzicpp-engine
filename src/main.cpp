// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  Main file in which Game loops.
//
//        Version:  1.0
//        Created:  06/16/2020 06:21:24 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include <iostream>
#include "game.hpp"
#include "constants.hpp"

int main(int arg, char* args[])
{
	Game game = Game::GetInstance();

	game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game.IsRunning()) {
		game.Update();
		game.Render();
	}

	game.Destroy();

	return 0;
}
