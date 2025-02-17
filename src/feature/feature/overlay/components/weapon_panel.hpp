#pragma once

#include "panel.hpp"
#include <feature/feature/overlay/context.hpp>
#include <feature/feature/overlay/overlay_config.hpp>
#include <imgui_manager/data.hpp>

namespace feature::visual::overlay {
    class c_weapon_panel final : public c_panel {
    public:
        explicit c_weapon_panel( overlay_context& context, const weapon_display_config_t& config = {} ) noexcept
            : m_context{ context }, m_config{ config } { }

    protected:
        bool on_render() noexcept override {
            if ( m_context.update() ) {
                render_weapon_info();
            }
            return true;
        }

    private:
        void render_weapon_info() noexcept {
            const auto& weapon = m_context.get_selected_weapon();
            const auto& text_pos = m_context.get_text_position();
            float current_y = text_pos.get_separator_y() + 10.0f;

            render_text_line( *weapon.name, current_y );
            current_y += m_config.vertical_spacing;

            if ( weapon.scope ) {
                render_text_line( *weapon.scope, current_y );
                current_y += m_config.vertical_spacing;
            }

            if ( weapon.module ) {
                render_text_line( *weapon.module, current_y );
            }
        }

        void render_text_line( std::string_view text, float y_pos ) noexcept {
            ImGui::PushFont( g_imgui_data.glory_bold );

            const auto& text_pos = m_context.get_text_position();
            ImGui::SetCursorPos( ImVec2( text_pos.x, y_pos ) );

            ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( m_config.text_color ), "%.*s", static_cast<int>( text.size() ), text.data() );

            ImGui::PopFont();
        }

    private:
        overlay_context& m_context;
        weapon_display_config_t m_config;
    };

} // namespace feature::visual::overlay