#include "weapon_registry.hpp"

#include <rust/weapon/modules/magazine/magazine_module.hpp>
#include <rust/weapon/weapons/rifle/rifle_entity.hpp>
#include <utils/logger.hpp>

namespace weapon {

    void weapon_registry::initialize() noexcept {
        m_factory.register_weapon( std::move( weapon_factory::create_weapon<rifle>( "AK47", 30, 133.0f ).add_extended_mag( 8 ).build() ) );

        CONSOLE_INFO( "Available weapon: {}\n", m_factory.weapon_count() );
        for ( const auto& name : m_factory.get_available_weapons() ) {
            CONSOLE_INFO( "{}\n", name.data() );
        }
    }

    weapon_factory& weapon_registry::get_factory() noexcept {
        return m_factory;
    }

} // namespace weapon