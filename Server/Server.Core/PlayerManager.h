#pragma once

#include <RPC3.h>
#include "EntityManager.h"
#include "AComponent.h"
#include "NetworkObject.h"
#include "RPC3.h"

class PlayerManager : public EntityManager, public NetworkObject
{
public:
	PlayerManager();
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	virtual void	createEntity(ecs::ClientId owner);
	virtual void	deleteEntity(ecs::ClientId owner);
	virtual void	updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	updateEntities();

	bool			isNicknameAvailable(const std::string& nickname)	const;

	void			setPlayerNickname(RakNet::RakString nickname, RakNet::RPC3* rpc);
};
