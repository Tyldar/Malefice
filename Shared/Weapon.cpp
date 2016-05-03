#include <iostream>
#include "Weapon.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", WEAPON),
		ID(0), WEAPON_NAME("Weapon"), MAX_AMMUNITION(0), MAX_AMMUNITION_EXPLOSIVE(0), DAMAGE(0), DAMAGE_EXPLOSIVE(0), WEAPON_TYPE(DEFAULT), HAND_TO_HAND(false)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const int id, const std::string& name, const int maxAmmunition, const int maxAmmunitionExplosive, const int damage, const int damageExplosive, const WeaponType weaponType, const bool handToHand) : AComponent("Weapon", WEAPON),
		ID(id), WEAPON_NAME(name), MAX_AMMUNITION(maxAmmunition), MAX_AMMUNITION_EXPLOSIVE(maxAmmunitionExplosive), DAMAGE(damage), DAMAGE_EXPLOSIVE(damageExplosive), WEAPON_TYPE(weaponType), HAND_TO_HAND(handToHand)
	{
		m_currentAmmunition = MAX_AMMUNITION;
		m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", WEAPON),
		ID(cpy.ID), WEAPON_NAME(cpy.NAME), MAX_AMMUNITION(cpy.MAX_AMMUNITION), MAX_AMMUNITION_EXPLOSIVE(cpy.MAX_AMMUNITION_EXPLOSIVE), DAMAGE(cpy.DAMAGE), DAMAGE_EXPLOSIVE(cpy.DAMAGE_EXPLOSIVE), WEAPON_TYPE(cpy.WEAPON_TYPE), HAND_TO_HAND(cpy.HAND_TO_HAND)
	{
		m_currentAmmunition = cpy.m_currentAmmunition;
		m_currentAmmunitionExplosive = cpy.m_currentAmmunitionExplosive;
	}

	Weapon& Weapon::operator=(const Weapon& other)
	{
		m_currentAmmunition = other.m_currentAmmunition;
		m_currentAmmunitionExplosive = other.m_currentAmmunitionExplosive;
		return *this;
	}

	void	Weapon::dump() const
	{
		std::cout << "[" << NAME << "/" << m_currentAmmunition << "/" << MAX_AMMUNITION << "/" << m_currentAmmunitionExplosive << "/" << MAX_AMMUNITION_EXPLOSIVE << "/" << DAMAGE << "/" << DAMAGE_EXPLOSIVE <<"]" << std::endl;
	}

	const int		Weapon::getDamage() const
	{
		return DAMAGE;
	}

	const int		Weapon::getDamageExplosive() const
	{
		return DAMAGE_EXPLOSIVE;
	}

	int			Weapon::getAmmunition() const
	{
		return m_currentAmmunition;
	}

	int			Weapon::getAmmunitionExplosive() const
	{
		return m_currentAmmunitionExplosive;
	}

	const Weapon::WeaponType Weapon::getWeaponType() const
	{
		return WEAPON_TYPE;
	}

	const bool		Weapon::isHandToHand() const
	{
		return HAND_TO_HAND;
	}
	const std::string & Weapon::getName() const
	{
		return WEAPON_NAME;
	}

	void Weapon::decAmmunition(int nbFired)
	{
		m_currentAmmunition -= nbFired;
		if (m_currentAmmunition < 0)
			m_currentAmmunition = 0;
	}

	void Weapon::decAmmunitionExplosive(int nbFired)
	{
		m_currentAmmunitionExplosive -= nbFired;
		if (m_currentAmmunitionExplosive < 0)
			m_currentAmmunitionExplosive = 0;
	}

	void Weapon::incAmmunition(int nbAmmuition)
	{
		m_currentAmmunition += nbAmmuition;
		if (m_currentAmmunition > MAX_AMMUNITION)
			m_currentAmmunition = MAX_AMMUNITION;
	}

	void Weapon::incAmmunitionExplosive(int nbAmmunition)
	{
		m_currentAmmunitionExplosive += nbAmmunition;
		if (m_currentAmmunitionExplosive > MAX_AMMUNITION_EXPLOSIVE)
			m_currentAmmunitionExplosive = MAX_AMMUNITION_EXPLOSIVE;
	}
};