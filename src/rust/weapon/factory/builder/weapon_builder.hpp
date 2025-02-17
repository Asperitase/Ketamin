#pragma once
#include <memory>
#include <rust/weapon/weapons/base/weapon_base.hpp>

namespace weapon {

    template <typename WeaponT>
    class weapon_builder {
    public:
        explicit weapon_builder( std::string_view name, size_t base_ammo, float fire_rate ) noexcept;
        weapon_builder& add_extended_mag( int additional_ammo ) noexcept;
        weapon_builder& add_module( std::string_view name, float modifier ) noexcept;
        [[nodiscard]] std::unique_ptr<WeaponT> build() noexcept;

    private:
        std::unique_ptr<WeaponT> m_weapon;
    };

} // namespace weapon