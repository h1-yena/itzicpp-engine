// =====================================================================================
//
//       Filename:  EntityManager.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  06/20/2020 05:20:36 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include "./entityManager.hpp"

EntityManager::EntityManager() {}

EntityManager& EntityManager::GetInstance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render(SDL_Renderer* renderer)
{
	for (auto& entity : entities) {
		entity->Render(renderer);
	}
}

bool EntityManager::HasNoEntities() const
{
	return entities.empty();
}

Entity& EntityManager::AddEntity(const std::string& entityName)
{
	Entity* entity = new Entity(*this, entityName);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

unsigned int EntityManager::GetEntityCount() const
{
	return entities.size();
}

void EntityManager::ClearData()
{
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

EntityManager::~EntityManager()
{
	ClearData();
	for (auto& entity : entities) {
		delete entity;
	}
}
