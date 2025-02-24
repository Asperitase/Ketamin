#pragma once

#include "panel.hpp"
#include <imgui_manager/data.hpp>

namespace feature::visual::overlay {

    class header_panel final : public panel {
    public:
        explicit header_panel( overlay_context& ctx, weapon_display_config_t& config, header_config_t& header_config ) noexcept
            : panel{ ctx }, m_config{ config }, m_header_config{ header_config } { }

        ~header_panel() noexcept override = default;

    protected:
        bool on_render() noexcept override {
            ImGui::PushFont( g_imgui_data.glory_bold );
            ImGui::SetCursorPos( { m_config.x, m_config.y } );
            ImGui::PushStyleColor( ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4( m_header_config.text_color ) );
            ImGui::Text( "%.*s", static_cast<int>( m_header_config.title.size() ), m_header_config.title.data() );
            ImGui::PopStyleColor();
            ImGui::PopFont();

            ImGui::PushFont( g_imgui_data.main_icon );
            ImGui::SetCursorPos( { m_config.x + m_header_config.icon_offset, m_config.y } );
            ImGui::PushStyleColor( ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4( m_header_config.icon_color ) );
            ImGui::Text( "%.*s", static_cast<int>( m_header_config.icon.size() ), m_header_config.icon.data() );
            ImGui::PopStyleColor();
            ImGui::PopFont();

            ImGui::SetCursorPosY( m_config.get_separator_y() );
            ImGui::Separator();

            return true;
        }

    private:
        weapon_display_config_t& m_config;
        header_config_t& m_header_config;
    };

} // namespace feature::visual::overlay