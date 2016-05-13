#pragma once

#include "Entity.h"

class EntityManager
{
public:
	EntityManager()	= default;
	~EntityManager();

	virtual void			createEntity(ecs::ClientId owner)	= 0;
	virtual void			deleteEntity(ecs::ClientId owner)	= 0;

	bool			hasEntity(ecs::ClientId owner)	const;
	ecs::Entity*	findEntity(ecs::ClientId owner)	const;


protected:
	std::map<ecs::ClientId, ecs::Entity*>	m_entities;
};