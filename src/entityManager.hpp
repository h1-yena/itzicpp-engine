// =====================================================================================
//
//       Filename:  entityManager.hpp
//
//    Description:  Manages all entities or game objects.
//
//        Version:  1.0
//        Created:  06/20/2020 05:17:20 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#pragma once

#include "./entity.hpp"
#include "./components/component.hpp"
#include <vector>
#include <SDL2/SDL_render.h>

class EntityManager
{
private:
	// Singleton
	EntityManager();

	std::vector<Entity*> entities;
public:
	// Singleton Instance
	static EntityManager& GetInstance();

	// Game Logic
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);
	void ClearData();

	// Utility Functions
	bool HasNoEntities() const;
	Entity& AddEntity(const std::string& entityName);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount() const;

	// Destructor
	~EntityManager();
};
