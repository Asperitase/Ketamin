#pragma once
#include <concepts>
#include <optional>
#include <rust/weapon/factory/builder/weapon_builder.hpp>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace weapon {

    template <typename T> concept weapon_type = std::derived_from<T, weapon_base>;
    class weapon_factory {
    public:
        explicit weapon_factory() noexcept {
            m_weapons.reserve( 32 );
        }

        weapon_factory( const weapon_factory& ) = delete;
        weapon_factory& operator=( const weapon_factory& ) = delete;

        weapon_factory( weapon_factory&& ) noexcept = default;
        weapon_factory& operator=( weapon_factory&& ) noexcept = default;

        template <weapon_type T>
        [[nodiscard]] static auto create_weapon( std::string_view name, size_t base_ammo, float fire_rate ) noexcept {
            return weapon_builder<T>( name, base_ammo, fire_rate );
        }

        void register_weapon( std::unique_ptr<weapon_base> weapon ) noexcept;
        [[nodiscard]] std::unique_ptr<weapon_base> get_weapon( std::string_view name ) noexcept;

        [[nodiscard]] std::vector<std::string_view> get_available_weapons() const noexcept;
        bool remove_weapon( std::string_view name ) noexcept;
        [[nodiscard]] bool has_weapon( std::string_view name ) const noexcept;
        [[nodiscard]] size_t weapon_count() const noexcept;

    private:
        std::unordered_map<std::string_view, std::unique_ptr<weapon_base>> m_weapons;
    };

} // namespace weapon