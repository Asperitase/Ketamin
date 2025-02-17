#pragma once

#include "overlay_types.hpp"
#include <array>
#include <feature/manager.hpp>
#include <optional>
#include <span>
#include <tuple>

namespace feature::visual::overlay {
    class overlay_context final {
    public:
        struct cached_indices_t {
            int weapon{ 0 };
            int scope{ 0 };
            int module{ 0 };

            [[nodiscard]] bool operator==( const cached_indices_t& other ) const noexcept {
                return weapon == other.weapon && scope == other.scope && module == other.module;
            }

            [[nodiscard]] bool operator!=( const cached_indices_t& other ) const noexcept {
                return !( *this == other );
            }
        };

        explicit overlay_context() noexcept = default;

        void init( const std::shared_ptr<c_setting>& weapon, const std::shared_ptr<c_setting>& scope, const std::shared_ptr<c_setting>& module ) noexcept {
            m_weapon_setting = weapon;
            m_scope_setting = scope;
            m_module_setting = module;
        }

        [[nodiscard]] bool update() noexcept {
            const bool needs_update = check_for_updates();
            if ( needs_update ) {
                update_cache();
            }
            return ( needs_update == 0 );
        }

        [[nodiscard]] const weapon_data_t& get_selected_weapon() const noexcept {
            return m_cached_weapon;
        }

        [[nodiscard]] constexpr const text_position_t& get_text_position() const noexcept {
            return m_text_pos;
        }

    private:
        [[nodiscard]] std::tuple<std::optional<int>, std::optional<int>, std::optional<int>> get_current_settings() const noexcept {
            auto& manager = feature::c_manager::instance();

            auto try_get_setting = [&manager]( const char* feature, const char* setting ) -> std::optional<int> {
                if ( auto setting_ptr = manager.get_settings_by_feature( feature, setting ) ) {
                    if ( auto value = setting_ptr->get_value(); value.has_value() ) {
                        return std::any_cast<int>( value );
                    }
                }
                return std::nullopt;
            };

            return { try_get_setting( "Overlay", "overlay.selected_weapon" ), try_get_setting( "Overlay", "overlay.selected_scope" ),
                     try_get_setting( "Overlay", "overlay.selected_module" ) };
        }

        [[nodiscard]] bool check_for_updates() noexcept {
            const auto [new_weapon, new_scope, new_module] = get_current_settings();

            if ( !new_weapon || !new_scope || !new_module ) {
                return false;
            }

            const cached_indices_t current_indices{ .weapon = *new_weapon, .scope = *new_scope, .module = *new_module };

            return current_indices != cached_indices_t{ m_cached_weapon_index, m_cached_scope_index, m_cached_module_index };
        }

        void update_cache() noexcept {
            const auto [weapon_idx_opt, scope_idx_opt, module_idx_opt] = get_current_settings();

            if ( !weapon_idx_opt || !scope_idx_opt || !module_idx_opt ) {
                return;
            }

            const int weapon_idx = *weapon_idx_opt;
            const int scope_idx = *scope_idx_opt;
            const int module_idx = *module_idx_opt;

            if ( weapon_idx >= 0 && weapon_idx < std::size( weapons_array ) && scope_idx >= 0 && scope_idx < std::size( scopes_array ) &&
                 module_idx >= 0 && module_idx < std::size( modules_array ) ) {

                m_cached_weapon = { weapons_array[weapon_idx], scopes_array[scope_idx], modules_array[module_idx] };

                m_cached_weapon_index = weapon_idx;
                m_cached_scope_index = scope_idx;
                m_cached_module_index = module_idx;
            }
        }

    private:
        std::shared_ptr<c_setting> m_weapon_setting;
        std::shared_ptr<c_setting> m_scope_setting;
        std::shared_ptr<c_setting> m_module_setting;

        weapon_data_t m_cached_weapon;
        int m_cached_weapon_index{ -1 };
        int m_cached_scope_index{ -1 };
        int m_cached_module_index{ -1 };
        text_position_t m_text_pos;
    };

} // namespace feature::visual::overlay