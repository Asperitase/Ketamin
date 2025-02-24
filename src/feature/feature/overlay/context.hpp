#pragma once

#include "overlay_types.hpp"
#include "weapon_types.hpp"
#include <array>
#include <expected>
#include <feature/manager.hpp>
#include <span>
#include <tuple>
#include <utils/bit_flags.hpp>

namespace feature::visual::overlay {
    enum class overlay_error {
        invalid_weapon_index,
        invalid_scope_index,
        invalid_module_index,
        settings_not_found
    };

    class overlay_context final {
    public:
        explicit overlay_context() noexcept = default;

        [[nodiscard]] bool update() noexcept {
            const auto flags = check_for_updates();
            if ( flags ) {
                return update_cache( flags );
            }
            return true;
        }

        [[nodiscard]] const weapon_data_t& get_selected_weapon() const noexcept {
            return m_weapon;
        }

    private:
        [[nodiscard]] std::expected<std::tuple<int, int, int>, overlay_error> get_current_settings() const noexcept {
            auto& manager = feature::c_manager::instance();

            auto try_get_setting = [&manager]( const char* setting ) noexcept -> std::expected<int, overlay_error> {
                if ( auto setting_ptr = manager.get_settings_by_feature( "Overlay", setting ) ) {
                    if ( auto value = setting_ptr->get_value(); value.has_value() ) {
                        if ( auto* int_value = std::any_cast<int>( &value ) ) {
                            return *int_value;
                        }
                    }
                }
                return std::unexpected( overlay_error::settings_not_found );
            };

            auto weapon = try_get_setting( "selected_weapon" );
            if ( !weapon )
                return std::unexpected( weapon.error() );

            auto scope = try_get_setting( "selected_scope" );
            if ( !scope )
                return std::unexpected( scope.error() );

            auto module = try_get_setting( "selected_module" );
            if ( !module )
                return std::unexpected( module.error() );

            return std::tuple{ *weapon, *scope, *module };
        }

        [[nodiscard]] bit_flags<update_overlay_slot_flags, uint8_t> check_for_updates() noexcept {
            bit_flags<update_overlay_slot_flags, uint8_t> flags{};

            auto settings = get_current_settings();
            if ( !settings ) {
                return flags;
            }

            const auto [new_weapon, new_scope, new_module] = *settings;

            if ( new_weapon != static_cast<int>( m_weapon.weapon ) ) {
                flags.set<update_overlay_slot_flags::weapon>();
            }
            if ( new_scope != static_cast<int>( m_weapon.scope ) ) {
                flags.set<update_overlay_slot_flags::scope>();
            }
            if ( new_module != static_cast<int>( m_weapon.module ) ) {
                flags.set<update_overlay_slot_flags::module>();
            }

            return flags;
        }

        bool update_cache( const bit_flags<update_overlay_slot_flags, uint8_t>& flags ) noexcept {
            auto settings = get_current_settings();
            if ( !settings ) {
                return false;
            }

            const auto [weapon_idx, scope_idx, module_idx] = *settings;

            if ( !detail::is_valid_index( static_cast<weapon_type>( weapon_idx ), detail::weapon_names ) ||
                 !detail::is_valid_index( static_cast<scope_type>( scope_idx ), detail::scope_names ) ||
                 !detail::is_valid_index( static_cast<module_type>( module_idx ), detail::module_names ) ) {
                return false;
            }

            if ( flags.has<update_overlay_slot_flags::weapon>() ) {
                m_weapon.weapon = static_cast<weapon_type>( weapon_idx );
            }
            if ( flags.has<update_overlay_slot_flags::scope>() ) {
                m_weapon.scope = static_cast<scope_type>( scope_idx );
            }
            if ( flags.has<update_overlay_slot_flags::module>() ) {
                m_weapon.module = static_cast<module_type>( module_idx );
            }

            return true;
        }

    private:
        weapon_data_t m_weapon;
    };

} // namespace feature::visual::overlay