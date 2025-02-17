#pragma once
#include <rust/weapon/factory/weapon_factory.hpp>

namespace weapon {

    class weapon_registry {
    public:
        static weapon_registry& instance() noexcept {
            static weapon_registry registry;
            return registry;
        }

        void initialize() noexcept;

        [[nodiscard]] weapon_factory& get_factory() noexcept;

    private:
        weapon_registry() = default;
        weapon_factory m_factory;
    };

    namespace utils {
        [[nodiscard]] inline auto get_weapon( std::string_view name ) {
            return weapon_registry::instance().get_factory().get_weapon( name );
        }

        template <typename WeaponT>
        [[nodiscard]] inline auto create_weapon( std::string_view name, size_t base_ammo, float fire_rate ) {
            return weapon_factory::create_weapon<WeaponT>( name, base_ammo, fire_rate );
        }
    } // namespace utils

} // namespace weapon