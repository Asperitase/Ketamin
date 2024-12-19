#include "watermark.hpp"

#include "../menu/imgui_data.hpp"

using namespace feature::visual::watermark;

c_watermark::c_watermark() noexcept: c_feature( "Watermark", "Show information for script.", category_t::APPEARANCE ) {
    /*testbool = std::make_shared<c_setting>("Test", "Test", false);
    settings_->add_settings(testbool);*/
}

void c_watermark::on_enable() noexcept { }

void c_watermark::on_disable() noexcept { }

void c_watermark::on_draw() noexcept {
    if ( !is_enabled() )
        return;

    ImGuiWindowClass window_class;
    window_class.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost | ImGuiViewportFlags_NoTaskBarIcon;
    ImGui::SetNextWindowClass( &window_class );
    ImGui::SetNextWindowSize( ImVec2( 252, 30 ), ImGuiCond_Always );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.f );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 10.f );
    ImGui::PushStyleColor( ImGuiCol_WindowBg, ImGui::ColorConvertFloat4ToU32( ImColor( 24, 23, 33, 255 ) ) );
    ImGui::Begin( "watermark", nullptr, ImGuiWindowFlags_NoDecoration );
    {

        constexpr float icon_pos_x = 15.0f;
        constexpr float text_pos_x = 70.0f;
        constexpr float fps_pos_x = 195.0f;

        ImGui::PushFont( imgui::data::g_imgui_data.main_icon );
        ImGui::SetCursorPos( ImVec2( icon_pos_x, 8 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "A" );
        ImGui::SetCursorPos( ImVec2( 170, 8 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "B" );
        ImGui::PopFont();

        ImGui::SetCursorPos( ImVec2( text_pos_x, 8 ) );
        ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "ketaminex" );
        ImGui::PopFont();
        ImGui::SetCursorPos( ImVec2( fps_pos_x, 8 ) );
        ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 206, 206, 222, 255 ) ), "%.0f fps", imgui::data::g_imgui_data.io->Framerate );
    }
    ImGui::End();
    ImGui::PopStyleVar( 2 );
    ImGui::PopStyleColor();
}

void c_watermark::on_menu() noexcept {
    ImGui::Checkbox( "Enable##c_watermark", &std::get<bool>( enabled_setting->get_value() ) );
}