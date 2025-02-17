#pragma once

#include <external/ImGui/imgui.h>
#include <feature/feature/overlay/overlay_types.hpp>

#include <utils/random_string.hpp>

namespace feature::visual::overlay {
    class c_panel {
    public:
        explicit c_panel( const panel_config_t& config = {} ) noexcept: m_config{ config }, m_visible{ false } { }

        virtual ~c_panel() noexcept = default;

        [[nodiscard]] bool render() noexcept {
            if ( !m_visible )
                return false;

            begin_panel();
            const bool result = on_render();
            end_panel();

            return result;
        }

        constexpr void set_visible( bool visible ) noexcept {
            m_visible = visible;
        }

        [[nodiscard]] constexpr bool is_visible() const noexcept {
            return m_visible;
        }

    protected:
        virtual bool on_render() noexcept = 0;

        [[nodiscard]] constexpr const panel_config_t& get_config() const noexcept {
            return m_config;
        }

        [[nodiscard]] constexpr const text_position_t& get_text_pos() const noexcept {
            return m_text_pos;
        }

    private:
        void begin_panel() noexcept {
            ImGuiWindowClass window_class;
            window_class.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost | ImGuiViewportFlags_NoTaskBarIcon;

            ImGui::SetNextWindowClass( &window_class );

            ImGui::SetNextWindowSize( ImVec2( m_config.width, m_config.height ), ImGuiCond_Always );

            ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, m_config.border_size );
            ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, m_config.rounding );

            const auto& bg = m_config.background_color;
            ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( bg[0], bg[1], bg[2], bg[3] ) );
            ImGui::Begin( random_string::get_stable().c_str(), nullptr, ImGuiWindowFlags_NoDecoration );
        }

        void end_panel() noexcept {
            ImGui::End();
            ImGui::PopStyleVar( 2 );
            ImGui::PopStyleColor();
        }

    private:
        panel_config_t m_config;
        text_position_t m_text_pos;
        bool m_visible;
    };

} // namespace feature::visual::overlay