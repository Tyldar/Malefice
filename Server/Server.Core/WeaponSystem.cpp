// SERVER VERSION

#include "WeaponSystem.h"
#include "PhysicsUtil.h"
#include "NodePickable.h"
#include "Armor.h"
#include "PlayerManager.h"
#include "ServerCore.h"
#include "PlayerInfos.h"
#include "LifeSystem.h"
#include "PositionSystem.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity* entityClient, Line3dWrapper* rayWrap, RakNet::RPC3* rpc)
	{
		WeaponManager*	weaponManager;
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(entityClient->getOwner());
		
		*entity = *entityClient;
		PositionSystem::updateScenePosition(*entity);
		ecs::SceneAnimatedMesh* scene = dynamic_cast<SceneAnimatedMesh*>((*entity)[ecs::AComponent::ComponentType::SCENE]);
		if ((weaponManager = dynamic_cast<WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			PhysicsUtil& physicsUtil = PhysicsUtil::getInstance();
			PlayerManager& playerManager = ServerCore::getInstance().getPlayerManager();
			irr::core::line3df ray = rayWrap->getLine();
			if (weapon.shoot())
			{
				irr::core::vector3df intersection;
				irr::core::triangle3df hitTriangle;
				irr::scene::ISceneNode* selectedSceneNode =
					physicsUtil.getSceneManager()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
						ray,
						intersection,
						hitTriangle,
						nodePickable::IS_PICKABLE,
						0);
  				if (selectedSceneNode && (selectedSceneNode->getID() & nodePickable::IS_SHOOTABLE) == nodePickable::IS_SHOOTABLE)
				{
					auto entities = playerManager.getEntities();
					for (auto& player : entities)
					{
						if (dynamic_cast<ecs::AScene *>((*player.second)[ecs::AComponent::ComponentType::SCENE])->getNode() == selectedSceneNode)
						{
							ecs::Life*	lifeTarget;
							ecs::Armor*	armorTarget;

							if ((armorTarget = dynamic_cast<ecs::Armor*>((*player.second)[ecs::AComponent::ComponentType::ARMOR])) != nullptr && (lifeTarget = dynamic_cast<ecs::Life*>((*player.second)[ecs::AComponent::ComponentType::LIFE])) != nullptr)
							{
								int rest = armorTarget->takeDamage(weapon.getDamage() * weapon.getAmmoPerShot());
								if (rest > 0)
								{
									rest = lifeTarget->takeDamage(rest);
									if (rest >= 0)
										LifeSystem::die(player.second);
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}
