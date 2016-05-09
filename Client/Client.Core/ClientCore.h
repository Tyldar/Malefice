#pragma once

#include "Singleton.h"
#include "GraphicUtil.h"
#include "NetworkModule.h"

class ClientCore : public Singleton<ClientCore>
{
	friend class Singleton<ClientCore>;

public:
	void			run();

	bool			isActive()			const;
	NetworkModule*	getNetworkModule()	const;
	GraphicUtil*	getGraphicModule()	const;

	void			setIsActive(bool isActive);

protected:
	ClientCore();
	~ClientCore();

private:
	bool	init();
	void	pulse();

	NetworkModule*	m_networkModule;
	GraphicUtil*	m_graphicModule;
	bool			m_isActive;
};
