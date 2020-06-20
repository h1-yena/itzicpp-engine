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

void EntityManager::Render()
{
	for (auto& entity : entities) {
		entity->Render();
	}
}

bool EntityManager::HasNoEntities() const
{
	return entities.empty();
}

Entity& EntityManager::AddEntity(const std::string& entityName)
{
	Entity* newEntity = new Entity(*this, entityName);
	entities.push_back(newEntity);
	return *newEntity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

void EntityManager::Destroy()
{
	if (!HasNoEntities()) {
		for (auto& entity : entities) {
			delete entity;
		}
	}
}

EntityManager::~EntityManager()
{
	Destroy();
}
