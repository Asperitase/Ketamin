#include "control.hpp"

#include <common/weapon_array.hpp>

#include <manager.hpp>

namespace feature::menu::control {
    c_control::c_control() noexcept: c_feature( "Control", "Control settings for weapon handling and recoil management", category_t::CONTROL ) {
        selected_weapon = settings_->initialize( "c_control.selected_weapon", "Currently selected weapon in the game", 0 );
        selected_scope = settings_->initialize( "c_control.selected_scope", "Currently selected scope in the game", 0 );
        selected_module = settings_->initialize( "c_control.selected_module", "Currently selected module in the game", 0 );
    }

    void c_control::on_draw() noexcept { }

    void c_control::on_menu() noexcept {
        ImGui::Checkbox( "Enable Control Recoil", &std::get<bool>( enabled_setting->get_value() ) );

        if ( is_enabled() ) {
            ImGui::Combo( "Weapon", &std::get<int>( selected_weapon->get_value() ), weapons_array, IM_ARRAYSIZE( weapons_array ) );
            ImGui::Combo( "Scope", &std::get<int>( selected_scope->get_value() ), scopes_array, IM_ARRAYSIZE( scopes_array ) );
            ImGui::Combo( "Module", &std::get<int>( selected_module->get_value() ), modules_array, IM_ARRAYSIZE( modules_array ) );
        }
    }

    void c_control::on_enabled() noexcept {
        if ( is_enabled() ) {
            
        }
    }

    void c_control::on_disabled() noexcept {
        if ( !is_enabled() ) {
            
        }
    }
} // namespace feature::menu::control