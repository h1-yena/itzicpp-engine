// =====================================================================================
//
//       Filename:  spriteComponent.hpp
//
//    Description:  Sprite Component.
//
//        Version:  1.0
//        Created:  06/20/2020 06:25:50 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include <iostream>
#include <cerrno>
#include <SDL2/SDL.h>
#include "../textureManager.hpp"
#include "../assetManager.hpp"
#include "./transformComponent.hpp"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destRect;

public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* textureId)
	{
		SetTexture(textureId);
	}

	void SetTexture(std::string assetTextureId)
	{
		texture = AssetManager::GetInstance().GetTexture(assetTextureId);
	}

	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		if (!transform) {
			std::cerr << "Unable to initialize sprite without transform component" << std::endl;
			exit(1);
		}
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = transform->width;
		sourceRect.h = transform->height;
	}

	void Update(float deltaTime) override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width * transform->scale.x;
		destRect.h = transform->height * transform->scale.y;
	}

	void Render(SDL_Renderer* renderer) override
	{
		TextureManager::Draw(renderer, texture, sourceRect, destRect, spriteFlip);
	}

	~SpriteComponent() override {}
};
