#pragma once
#include "weapon_base.hpp"
#include <rust/weapon/modules/magazine/magazine_module.hpp>
#include <rust/weapon/modules/modifier_module/modifier_module.hpp>

namespace weapon {

    weapon_base::weapon_base( std::string_view name, size_t base_ammo, float fire_rate ) noexcept
        : m_name( name ), m_base_ammo( base_ammo ), m_fire_rate( fire_rate ) { }

    [[nodiscard]] std::string_view weapon_base::get_name() const noexcept {
        return m_name;
    }

    [[nodiscard]] size_t weapon_base::get_base_ammo() const noexcept {
        return m_base_ammo;
    }

    [[nodiscard]] float weapon_base::get_fire_rate() const noexcept {
        return m_fire_rate;
    }

    template <typename T>
    void weapon_base::add_module( std::unique_ptr<T> module ) {
        static_assert( std::is_base_of_v<modules::i_module, T>, "Module must inherit from i_module" );

        if ( module ) {
            m_modules.add_module( std::move( module ) );
        }
    }

    template <typename T>
    [[nodiscard]] T* weapon_base::get_module( std::string_view name ) const noexcept {
        return m_modules.get_module<T>( name );
    }

    template void weapon_base::add_module<modules::magazine_module>( std::unique_ptr<modules::magazine_module> );
    template void weapon_base::add_module<modules::modifier_module>( std::unique_ptr<modules::modifier_module> );
    template modules::magazine_module* weapon_base::get_module<modules::magazine_module>( std::string_view ) const noexcept;
    template modules::modifier_module* weapon_base::get_module<modules::modifier_module>( std::string_view ) const noexcept;

} // namespace weapon