#pragma once

#include <external/ImGui/imgui.h>
#include <span>
#include <string_view>
#include <vector>

namespace ImGui {

    template <typename T>
    bool Combo( const char* label, T* current_item, std::span<const std::string_view> items, ImGuiComboFlags flags = 0 ) noexcept {
        static thread_local std::vector<const char*> cache;
        static thread_local ImGuiTextFilter filter;
        bool value_changed = false;

        const char* preview_value = items[static_cast<size_t>( *current_item )].data();

        if ( ImGui::BeginCombo( label, preview_value, flags ) ) {
            if ( ImGui::IsWindowAppearing() ) {
                ImGui::SetKeyboardFocusHere();
                filter.Clear();
            }

            ImGui::SetNextItemShortcut( ImGuiMod_Ctrl | ImGuiKey_F );
            filter.Draw( "##Filter", -FLT_MIN );

            cache.clear();
            cache.reserve( items.size() );

            for ( size_t i = 0; i < items.size(); ++i ) {
                const char* item_text = items[i].data();
                cache.push_back( item_text );

                if ( filter.PassFilter( item_text ) ) {
                    const bool is_selected = ( static_cast<size_t>( *current_item ) == i );
                    if ( ImGui::Selectable( item_text, is_selected ) ) {
                        *current_item = static_cast<T>( i );
                        value_changed = true;
                    }
                }
            }

            ImGui::EndCombo();
        }

        return value_changed;
    }

} // namespace ImGui
