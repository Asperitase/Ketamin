#include "overlay.hpp"

#include "../menu/imgui_data.hpp"

using namespace feature::visual::overlay;

c_overlay::c_overlay() noexcept: c_feature( "Overlay", "Renders window with script selections.", category_t::APPEARANCE ) { }

void c_overlay::on_enable() noexcept { }

void c_overlay::on_disable() noexcept { }

void c_overlay::on_draw() noexcept {
    if ( !is_enabled() )
        return;

    ImGuiWindowClass window_class;
    window_class.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost | ImGuiViewportFlags_NoTaskBarIcon;
    ImGui::SetNextWindowClass( &window_class );
    ImGui::SetNextWindowSize( ImVec2( 185, 125 ), ImGuiCond_Always );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.f );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 10.f );
    ImGui::PushStyleColor( ImGuiCol_WindowBg, ImGui::ColorConvertFloat4ToU32( ImColor( 24, 23, 33, 255 ) ) );
    ImGui::Begin( "overlay", nullptr, ImGuiWindowFlags_NoDecoration );
    {
        constexpr float text_pos_x = 20.f;
        constexpr float text_pos_y = 15.f;
        constexpr float sep_pos_y = text_pos_y + 30.f;

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

        ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
        ImGui::SetCursorPos( ImVec2( text_pos_x, sep_pos_y + 10 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ), "Assault Rifle" );
        ImGui::PopFont();

        ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
        ImGui::SetCursorPos( ImVec2( text_pos_x, sep_pos_y + 30 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ), "Holosight Scope" );
        ImGui::PopFont();

        ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
        ImGui::SetCursorPos( ImVec2( text_pos_x, sep_pos_y + 50 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ), "Muzzle Boost" );
        ImGui::PopFont();
    }
    ImGui::End();
    ImGui::PopStyleVar( 2 );
    ImGui::PopStyleColor();
}

void c_overlay::on_menu() noexcept {
    ImGui::Checkbox( "Enable##c_overlay", &std::get<bool>( enabled_setting->get_value() ) );
}