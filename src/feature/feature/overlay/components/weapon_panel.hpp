#pragma once

#include "panel.hpp"
#include <feature/feature/overlay/context.hpp>
#include <imgui_manager/data.hpp>

namespace feature::visual::overlay {
    class weapon_panel final : public panel {
    protected:
        bool on_render() noexcept override {
            if ( m_context.update() ) {
                render_weapon_info();
            }

            return true;
        }

    public:
        explicit weapon_panel( overlay_context& ctx, weapon_display_config_t& config ) noexcept: panel{ ctx }, m_context{ ctx }, m_config{ config } { }

    private:
        void render_weapon_info() noexcept {
            const auto& weapons = m_context.get_selected_weapon();
            float current_y = m_config.get_separator_y() + 10.0f;

            if ( weapons.has_item<weapon_type>( weapons.weapon ) ) {
                render_text_line( to_string( weapons.weapon, detail::weapon_names ), current_y );
            }

            if ( weapons.has_item<scope_type>( weapons.scope ) ) {
                render_text_line( to_string( weapons.scope, detail::scope_names ), current_y );
            }

            if ( weapons.has_item<module_type>( weapons.module ) ) {
                render_text_line( to_string( weapons.module, detail::module_names ), current_y );
            }
        }

        void render_text_line( std::string_view text, float& y_pos ) noexcept {
            ImGui::PushFont( g_imgui_data.glory_bold );
            ImGui::SetCursorPos( ImVec2( m_config.x, y_pos ) );
            ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( m_config.text_color ), "%.*s", static_cast<int>( text.size() ), text.data() );
            ImGui::PopFont();
            y_pos += m_config.vertical_spacing;
        }

    private:
        overlay_context& m_context;
        weapon_display_config_t& m_config;
    };

} // namespace feature::visual::overlay