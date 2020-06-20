// =====================================================================================
//
//       Filename:  transform.hpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 05:41:41 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <glm/glm.hpp>
#include "./component.hpp"
#include "../entityManager.hpp"
#include <SDL2/SDL.h>

class TransformComponent : public Component
{
private:
	// Positional attributes
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 scale;
	float rotation;

	// Size
	int width;
	int height;

public:
	TransformComponent(int posX, int posY,
										 int velX, int velY,
										 int scaX, int scaY,
										 int width, int height)
		: position(glm::vec2(posX, posY))
		, velocity(glm::vec2(velX, velY))
		, scale(glm::vec2(scaX, scaY))
		, rotation(0)
		, width(width), height(height)
	{}

	void Initialize() override {}

	void Update(float deltaTime) override
	{
		// Update the position/velocity as a function of deltaTime.
		position += velocity * deltaTime;
	}

	void Render(SDL_Renderer& renderer) override
	{
		SDL_Rect transformRectangle {
			(int)position.x,
			(int)position.y,
			width,
			height
		};

		SDL_SetRenderDrawColor(&renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(&renderer, &transformRectangle);
	}
	~TransformComponent() override {};
};
