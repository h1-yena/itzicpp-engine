// =====================================================================================
//
//       Filename:  entity.hpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 05:06:47 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL_render.h>
#include "./components/component.hpp"

class EntityManager;

class Entity
{
private:
	EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;

public:
	std::string name;

	Entity(EntityManager& manager);
	Entity(EntityManager& manager, const std::string& name);

	// Game Logic
	void Update(float deltaTime);
	void Render(SDL_Renderer& renderer);
	void Destroy();

	// Add Generic Component
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&& ... args)
	{
		T* component = new T(std::forward<TArgs>(args)...);
		component->owner = this;
		components.emplace_back(component);
		component->Initialize();
		return* component;
	}

	// Getters & Setters
	bool IsActive() const;

	// Destructor
	~Entity();
};
