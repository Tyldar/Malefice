#include "Entity.h"

namespace ecs
{
	static int nextID()
	{
		static int id = 0;
		return id++;
	}

	Entity::Entity() :
		ID(nextID())
	{

	}

	AComponent*& Entity::operator[](ComponentType type)
	{
		return m_mComponents[type];
	}

	bool Entity::has(ComponentType type)
	{
		try
		{
			m_mComponents.at(type);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

}