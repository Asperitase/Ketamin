#include "control.hpp"

#include "../menu/imgui_data.hpp"

#include <common/name_selector.hpp>

using namespace feature::visual::control;

c_control::c_control() noexcept: c_feature( "Control", "Selection", category_t::CONTROL ) {
    current_weapon = std::make_shared<c_setting>( "Weapon", "Current Seletion Weapon", 0 );

    settings_->add_settings( current_weapon );
}

void c_control::on_enable() noexcept { }

void c_control::on_disable() noexcept { }

void c_control::on_draw() noexcept { }

void c_control::on_menu() noexcept {
    ImGui::Checkbox( "Enable##c_control", &std::get<bool>( enabled_setting->get_value() ) );

    if ( is_enabled() ) {
        ImGui::Combo( "Weapon", &std::get<int>( current_weapon->get_value() ), weapons_array, IM_ARRAYSIZE( weapons_array ) );
    }
}