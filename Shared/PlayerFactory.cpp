#include "PlayerFactory.h"
#include "ObjectFactory.h"
#include "CollectionComponent.h"
#include "Life.h"
#include "NetworkID.h"
#include "Team.h"

namespace factory
{
	ecs::Entity& player(ecs::Entity& entity, networkID network_id, int team)
	{
		object(entity);
		entity[ecs::LIFE] = new ecs::Life(100);
		entity[ecs::NETWORK_ID] = new ecs::NetworkID(network_id);
		entity[ecs::COMPONENT_TEAM] = new ecs::Team(team);
		return entity;
	}

	ecs::Entity& predator(ecs::Entity& entity, networkID network_id)
	{
		object(entity);
		entity[ecs::LIFE] = new ecs::Life(1000);
		entity[ecs::NETWORK_ID] = new ecs::NetworkID(network_id);
		entity[ecs::COMPONENT_TEAM] = new ecs::Team(0);
		return entity;
	}
}