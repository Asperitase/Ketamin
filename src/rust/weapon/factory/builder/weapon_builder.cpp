#include "weapon_builder.hpp"
#include <rust/weapon/modules/magazine/magazine_module.hpp>
#include <rust/weapon/modules/modifier_module/modifier_module.hpp>
#include <rust/weapon/modules/name.hpp>
#include <rust/weapon/weapons/other/other_entity.hpp>
#include <rust/weapon/weapons/pistol/pistol_entity.hpp>
#include <rust/weapon/weapons/rifle/rifle_entity.hpp>
#include <rust/weapon/weapons/semi/semi_entity.hpp>
#include <rust/weapon/weapons/shotgun/shotgun_entity.hpp>
#include <rust/weapon/weapons/smg/smg_entity.hpp>
#include <rust/weapon/weapons/sniper/sniper_entity.hpp>

namespace weapon {

    template <typename WeaponT>
    weapon_builder<WeaponT>::weapon_builder( std::string_view name, size_t base_ammo, float fire_rate ) noexcept
        : m_weapon( std::make_unique<WeaponT>( name, base_ammo, fire_rate ) ) { }

    template <typename WeaponT>
    weapon_builder<WeaponT>& weapon_builder<WeaponT>::add_extended_mag( int additional_ammo ) noexcept {
        m_weapon->add_module( std::make_unique<modules::magazine_module>( modules::name::magazine, additional_ammo ) );
        return *this;
    }

    template <typename WeaponT>
    weapon_builder<WeaponT>& weapon_builder<WeaponT>::add_module( std::string_view name, float modifier ) noexcept {
        m_weapon->add_module( std::make_unique<modules::modifier_module>( name, modifier ) );
        return *this;
    }

    template <typename WeaponT>
    std::unique_ptr<WeaponT> weapon_builder<WeaponT>::build() noexcept {
        return std::move( m_weapon );
    }

    template class weapon_builder<rifle>;
    template class weapon_builder<semi>;
    template class weapon_builder<smg>;
    template class weapon_builder<sniper>;
    template class weapon_builder<pistol>;
    template class weapon_builder<shotgun>;
    template class weapon_builder<other>;

} // namespace weapon