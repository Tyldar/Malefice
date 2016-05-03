#include "PlayerFactory.h"
#include "Life.h"
#include "NetworkID.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "Position.h"
#include "SpellManager.h"
#include "Spell.h"

ecs::Entity* PlayerFactory::createPlayer(float x, float y, float z, unsigned int networkId, int team, int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(x, y, z);

		(*entity)[ecs::LIFE] = new ecs::Life(life);
		(*entity)[ecs::NETWORK_ID] = new ecs::NetworkID(networkId);
		(*entity)[ecs::TEAM] = new ecs::Team(team);
		(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon("gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true));
		(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(x, y, z));
		(*entity)[ecs::SPELL] = new ecs::Spell(ecs::Spell::SpellType::NOTHING, 60);

		return entity;
	}

ecs::Entity* PlayerFactory::createPredator(float x, float y, float z, unsigned int networkId)
	{
	ecs::Entity* entity = PlayerFactory::createPlayer(x, y, z, networkId, 2, 1000);

		(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(ecs::Spell::CONFUSION, 5));

		return entity;
	}
