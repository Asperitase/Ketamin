#include "weapon_factory.hpp"
#include <rust/weapon/weapons/other/other_entity.hpp>
#include <rust/weapon/weapons/pistol/pistol_entity.hpp>
#include <rust/weapon/weapons/rifle/rifle_entity.hpp>
#include <rust/weapon/weapons/semi/semi_entity.hpp>
#include <rust/weapon/weapons/shotgun/shotgun_entity.hpp>
#include <rust/weapon/weapons/smg/smg_entity.hpp>
#include <rust/weapon/weapons/sniper/sniper_entity.hpp>

namespace weapon {

    void weapon_factory::register_weapon( std::unique_ptr<weapon_base> weapon ) noexcept {
        if ( weapon && !has_weapon( weapon->get_name() ) ) {
            m_weapons.emplace( weapon->get_name(), std::move( weapon ) );
        }
    }

    std::unique_ptr<weapon_base> weapon_factory::get_weapon( std::string_view name ) noexcept {
        if ( auto it = m_weapons.find( name ); it != m_weapons.end() ) {
            auto weapon = std::move( it->second );
            m_weapons.erase( it );
            return weapon;
        }
        return nullptr;
    }

    std::vector<std::string_view> weapon_factory::get_available_weapons() const noexcept {
        std::vector<std::string_view> names;
        names.reserve( m_weapons.size() );
        for ( const auto& [name, _] : m_weapons ) {
            names.push_back( name );
        }
        return names;
    }

    bool weapon_factory::remove_weapon( std::string_view name ) noexcept {
        return m_weapons.erase( name ) > 0;
    }

    bool weapon_factory::has_weapon( std::string_view name ) const noexcept {
        return m_weapons.contains( name );
    }

    size_t weapon_factory::weapon_count() const noexcept {
        return m_weapons.size();
    }

} // namespace weapon