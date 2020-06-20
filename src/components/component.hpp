// =====================================================================================
//
//       Filename:  component.hpp
//
//    Description:  Base class that all components inherit from.
//
//        Version:  1.0
//        Created:  06/20/2020 05:04:18 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <SDL2/SDL_render.h>

class Entity;

class Component
{
public:
	Entity* owner;
	virtual ~Component() {};
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
};
