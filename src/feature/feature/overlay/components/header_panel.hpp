#pragma once

#include "panel.hpp"
#include <imgui_manager/data.hpp>

#include <feature/feature/overlay/overlay_config.hpp>

namespace feature::visual::overlay {
    class c_header_panel final : public c_panel {
    public:
        explicit c_header_panel( const header_config_t& header_config = {} ) noexcept: m_header_config{ header_config } { }

    protected:
        bool on_render() noexcept override {
            render_title();
            render_icon();

            ImGui::SetCursorPosY( get_text_pos().get_separator_y() );
            ImGui::Separator();

            return true;
        }

    private:
        const float& x = get_text_pos().x;
        const float& y = get_text_pos().y;

        void render_title() noexcept {
            ImGui::PushFont( g_imgui_data.glory_bold );

            ImGui::SetCursorPos( ImVec2( x, y ) );

            const auto& text_color = m_header_config.text_color;
            ImGui::TextColored( ImVec4( text_color[0], text_color[1], text_color[2], text_color[3] ), "%.*s",
                                static_cast<int>( m_header_config.title.size() ), m_header_config.title.data() );

            ImGui::PopFont();
        }

        void render_icon() noexcept {
            ImGui::PushFont( g_imgui_data.main_icon );

            ImGui::SetCursorPos( ImVec2( x + m_header_config.icon_offset, y ) );

            const auto& icon_color = m_header_config.icon_color;
            ImGui::TextColored( ImVec4( icon_color[0], icon_color[1], icon_color[2], icon_color[3] ), "%.*s",
                                static_cast<int>( m_header_config.icon.size() ), m_header_config.icon.data() );

            ImGui::PopFont();
        }

    private:
        header_config_t m_header_config;
    };
} // namespace feature::visual::overlay