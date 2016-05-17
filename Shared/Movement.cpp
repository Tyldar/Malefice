#include "Movement.h"

namespace ecs
{
	Movement::Movement() : AComponent("Movement", ecs::AComponent::ComponentType::MOVEMENT),
		m_destination()
	{
	}

	Movement::Movement(const Position& position) : AComponent("Movement", ecs::AComponent::ComponentType::MOVEMENT),
		m_destination(position)
	{
	}


	void	Movement::init()
	{
		// TODO: implement constructor logic here
	}


	void Movement::setDestination(const Position& newDestination)
	{
		m_destination = newDestination;
	}

	const Position& Movement::getDestination() const
	{
		return m_destination;
	}


	void Movement::move(Position& startPosition) const
	{
		if (m_destination != startPosition)
			startPosition = m_destination;
	}


	void	Movement::dump(std::ostream& os)	const
	{
		os << "Movement {destination = " << m_destination << "}";
	}


	void	Movement::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		m_destination.serialize(out, false);
	}

	void	Movement::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		m_destination.deserialize(in);
	}
}
