#pragma once

#include <RPC4Plugin.h>

#include "../../Shared/NetworkRPC.h"
#include "../../Shared/StdInc.h"

class GeneralRPC
{
private:
	static bool		m_bRegistered;

public:
	static void		Register(RakNet::RPC4 * pRPC);
	static void		Unregister(RakNet::RPC4 * pRPC);
};