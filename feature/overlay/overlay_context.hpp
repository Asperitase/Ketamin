#ifndef FEATURE_OVERLAY_CONTEXT_HPP
#define FEATURE_OVERLAY_CONTEXT_HPP

#include <manager.hpp>

#include <common/weapon_name_array.hpp>

namespace feature::visual::overlay {
    struct overlay_context_t {
        [[nodiscard]] auto get_selected_arsenal( const std::string_view params ) const noexcept {
            return manager::get_value_from_class<int>( "Control", "c_control.selected_weapon" ).value();
        }

        void update() const noexcept {
            ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
            ImGui::SetCursorPos( ImVec2( text::text_pos_x, text::sep_pos_y + 10 ) );
            ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ),
                                weapons_array[get_selected_arsenal( "c_control.selected_weapon" )] );
            ImGui::PopFont();
            ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
            ImGui::SetCursorPos( ImVec2( text::text_pos_x, text::sep_pos_y + 30 ) );
            ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ),
                                weapons_array[get_selected_arsenal( "c_control.selected_weapon" )] );
            ImGui::PopFont();
            ImGui::PushFont( imgui::data::g_imgui_data.glory_bold );
            ImGui::SetCursorPos( ImVec2( text::text_pos_x, text::sep_pos_y + 50 ) );
            ImGui::TextColored( ImGui::ColorConvertU32ToFloat4( ImColor( 249, 249, 250, 255 ) ),
                                weapons_array[get_selected_arsenal( "c_control.selected_weapon" )] );
            ImGui::PopFont();
        }
    };
} // namespace feature::visual::overlay

#endif // !FEATURE_OVERLAY_CONTEXT_HPP
