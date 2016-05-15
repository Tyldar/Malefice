#pragma once

#include <map>
#include <BitStream.h>
#include "Weapon.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT WeaponManager : public AComponent
	{
	public:
		WeaponManager();
		WeaponManager(Weapon& defaultWeapon);
		~WeaponManager()	= default;

		void			addWeapon(Weapon& newWeapon);
		void			changeToNextWeapon();
		void			changeToPrecWeapon();

		Weapon&									getCurrentWeapon()	const;
		std::map<Weapon::WeaponType, Weapon&>&	getWeapons();

		void			createWeapon(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const Weapon& weaponCpy);


		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		std::map<Weapon::WeaponType, Weapon&>			m_weapons;
		std::map<Weapon::WeaponType, Weapon&>::iterator	m_currentWeapon;
	};
}
