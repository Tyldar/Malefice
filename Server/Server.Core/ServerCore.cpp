#include <iostream>
#include "ServerCore.h"
#include "ProjectGlobals.h"
#include "Logger.h"
#include "Utility.h"

ServerCore::ServerCore() :
	m_startTime(0), m_isActive(false), m_configuration(), m_networkModule(nullptr), m_inputQueue(), m_inputMutex(), m_readInput(), m_inputThread()
{
}


void	ServerCore::run()
{
	LOG_INFO(GENERAL) << "Server started.";
	if (this->init() == false)
	{
		LOG_CRITICAL(GENERAL) << "Server initialization failed. Abortring.";
		return;
	}
	LOG_INFO(GENERAL) << "Server initialized.";
	while (m_isActive)
	{
		this->pulse();
		this->handleInput();
	}
	this->stop();
	LOG_INFO(GENERAL) << "Server stopped.";
}

bool	ServerCore::init()
{
	if (m_configuration.loadFromFile(ServerCoreConfiguration::DEFAULT_SETTINGS_FILENAME) == false)
		return false;
	m_networkModule = new NetworkModule();
	if (m_networkModule->init(m_configuration.getAddress(), m_configuration.getPort(), m_configuration.getPassword()) == false)
	{
		LOG_CRITICAL(NETWORK) << "Failed to start Network Module.";
		return false;
	}
	m_playerManager = new PlayerManager();
	m_isActive = true;
	m_readInput = true;
	m_inputThread = std::thread(&ServerCore::readInput, this);
	m_startTime = utility::getMsTime();
	this->displayHeader();
	return true;
}

void	ServerCore::stop()
{
	m_readInput = false;
	m_inputThread.join();
}

void	ServerCore::displayHeader()	const
{
	std::string	title = ProjectGlobals::GAME_NAME + " v." + ProjectGlobals::GAME_SERVER_VERSION;

#ifdef WIN32
	SetConsoleTitle(title.c_str());
#endif

	std::cout << "==============================================================" << std::endl;
	std::cout << "                         " << title << std::endl;
	std::cout << "==============================================================" << std::endl;
	std::cout << "=Server Name	: " << m_configuration.getName() << std::endl;
	std::cout << "=Server Port	: " << m_configuration.getPort() << std::endl;
	std::cout << "=Max Players	: " << ProjectGlobals::MAX_PLAYERS_NB << std::endl;
	if (m_configuration.getPassword().length() > 0)
		std::cout << "=Password	: " << m_configuration.getPassword() << std::endl;
	std::cout << "==============================================================" << std::endl;

}


void	ServerCore::pulse()
{
	if (m_networkModule != nullptr)
		m_networkModule->pulse();
}


void	ServerCore::readInput()
{
	while (m_readInput)
	{
		std::string	input;

		std::getline(std::cin, input);
		m_inputMutex.lock();
		m_inputQueue.push(input);
		m_inputMutex.unlock();
	}
}

void	ServerCore::handleInput()
{
	if (m_inputMutex.try_lock())
	{
		while (!m_inputQueue.empty())
		{
			std::string	input = m_inputQueue.back();
			std::size_t	paramsOffset = input.find(" ") + 1;
			std::string	command = input.substr(0, paramsOffset - 1);
			std::string	params = input.substr(paramsOffset);

			if (input.empty())
			{
				m_inputMutex.unlock();
				return;
			}
			this->processCommand(command, params);
			m_inputQueue.pop();
		}
		m_inputMutex.unlock();
	}
}

void	ServerCore::processCommand(const std::string& command, const std::string& params)
{
	if (command == "exit" || command == "quit" || command == "shutdown")
	{
		m_isActive = false;
		std::cout << "Press RETURN to close this window..." << std::endl;
	}
	else if (command == "uptime")
	{
		LOG_INFO(GENERAL) << "Current uptime: " << utility::getElapsedTimeSince(m_startTime);
	}
}



NetworkModule	*ServerCore::getNetworkModule()	const
{
	return m_networkModule;
}

PlayerManager	*ServerCore::getPlayerManager() const
{
	return m_playerManager;
}