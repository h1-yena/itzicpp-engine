// =====================================================================================
//
//       Filename:  entity.cpp
//
//    Description:  Implementation of Entity.
//
//        Version:  1.0
//        Created:  06/20/2020 05:11:22 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Itziar Morales Rodríguez (IMR), itzimr97@outlook.com
//   Organization:  UTAD
//
// =====================================================================================
#include "./entity.hpp"
#include "./components/component.hpp"

Entity::Entity(EntityManager& manager)
	: manager(manager)
	, isActive(true)
{}

Entity::Entity(EntityManager& manager, const std::string& name)
	: manager(manager)
	, isActive(true)
	, name(name)
{}

void Entity::Update(float deltaTime)
{
	for (auto& component  : components) {
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : components) {
		component->Render();
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::IsActive() const
{
	return this->isActive;
}

Entity::~Entity()
{
	if (components.empty()) {
		for (auto& component : components) {
			delete component;
		}
	}
}
