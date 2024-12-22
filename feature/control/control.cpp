#include "control.hpp"

#include <common/weapon_name_selector.hpp>

namespace feature::menu::control {
    c_control::c_control() noexcept: c_feature( "Control", "Control settings for weapon handling and recoil management", category_t::CONTROL ) {
        selected_weapon = settings_->initialize( "c_control.selected_weapon", "Currently selected weapon in the game", 0 );
    }

    void c_control::on_draw() noexcept { }

    void c_control::on_menu() noexcept {
        ImGui::Checkbox( "Enable Control Recoil", &std::get<bool>( enabled_setting->get_value() ) );

        if ( is_enabled() ) {
            ImGui::Combo( "Weapon", &std::get<int>( selected_weapon->get_value() ), weapons_array, IM_ARRAYSIZE( weapons_array ) );
        }
    }
} // namespace feature::menu::control