#ifndef FEATURE_OVERLAY_PANEL_HPP
#define FEATURE_OVERLAY_PANEL_HPP

#include <functional>

#include "overlay_params.hpp"

#include "overlay_context.hpp"

auto create_header_panel() noexcept {
    using namespace feature::visual::overlay::text;

    ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
    ImGui::SetCursorPos( ImVec2( text_pos_x, text_pos_y ) );
    ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "Weapon Selected" );
    ImGui::PopFont();
    ImGui::PushFont( imgui::data::g_imgui_data.main_icon );
    ImGui::SetCursorPos( ImVec2( text_pos_x + 130.f, text_pos_y ) );
    ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "E" );
    ImGui::PopFont();
    ImGui::SetCursorPosY( sep_pos_y );
    ImGui::Separator();
}

auto create_overlay_panel( std::function<void( feature::visual::overlay::overlay_context_t& )> code ) noexcept {
    using namespace feature::visual::overlay::panel;

    ImGuiWindowClass window_class;
    window_class.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost | ImGuiViewportFlags_NoTaskBarIcon;

    ImGui::SetNextWindowClass( &window_class );
    ImGui::SetNextWindowSize( ImVec2( width, height ), ImGuiCond_Always );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, border_size );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, rounding );
    ImGui::PushStyleColor( ImGuiCol_WindowBg, ImGui::ColorConvertFloat4ToU32( bg_color ) );

    ImGui::Begin( "Overlay Menu##make random", nullptr, ImGuiWindowFlags_NoDecoration );
    {
        create_header_panel();
        feature::visual::overlay::overlay_context_t context;
        code( context );
    }
    ImGui::End();

    ImGui::PopStyleVar( 2 );
    ImGui::PopStyleColor();
}

#endif // !FEATURE_OVERLAY_PANEL_HPP
