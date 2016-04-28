#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager(weapon::AWeapon *defaultWeapon) : AComponent("WeaponManager", WEAPON_MANAGER)
	{
		m_vWeapons.push_back(defaultWeapon);
		m_iCurrentWeapon = 0;
	}

	void	WeaponManager::addWeapon(weapon::AWeapon *newWeapon)
	{
		m_vWeapons.push_back(newWeapon);
	}

	void WeaponManager::changeToNextWeapon()
	{
		m_iCurrentWeapon++;
		if (m_iCurrentWeapon == m_vWeapons.size())
			m_iCurrentWeapon = 0;
	}

	void WeaponManager::changeToPrecWeapon()
	{
		m_iCurrentWeapon--;
		if (m_iCurrentWeapon == -1)
			m_iCurrentWeapon = m_vWeapons.size() - 1;
	}

	weapon::AWeapon *WeaponManager::getCurrentWeapon() const
	{
		return m_vWeapons[m_iCurrentWeapon];
	}

	void WeaponManager::dump() const
	{
		for (auto it = m_vWeapons.begin(); it != m_vWeapons.end(); --it)
		{
			(*it)->dump();
		}
	}
}
