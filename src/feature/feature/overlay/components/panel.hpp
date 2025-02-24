#pragma once

#include <external/ImGui/imgui.h>
#include <external/ImGui/imgui_internal.h>
#include <feature/feature/overlay/overlay_types.hpp>
#include <utils/random_string.hpp>

#include <feature/feature/overlay/context.hpp>

namespace feature::visual::overlay {

    class panel {
    public:
        explicit panel( overlay_context& ctx ) noexcept: m_context{ ctx }, m_visible{ false } {
            m_window_name = random_string::get_stable();
        }

        virtual ~panel() noexcept = default;

        panel( const panel& ) = delete;
        panel& operator=( const panel& ) = delete;

        panel( panel&& ) noexcept = default;
        panel& operator=( panel&& ) noexcept = default;

        bool render() noexcept {
            if ( !m_visible ) {
                return false;
            }

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

    private:
        void begin_panel() noexcept {
            const auto& weapons = m_context.get_selected_weapon();
            float additional_height = weapons.additional_height( weapons.weapon, 20.f ) + weapons.additional_height( weapons.scope, 20.f ) +
                                      weapons.additional_height( weapons.module, 20.f );

            m_config.animated_height = ImLerp( m_config.animated_height, 70.f + additional_height, ImGui::GetIO().DeltaTime * 13.f );

            ImGuiWindowClass window_class;
            window_class.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost | ImGuiViewportFlags_NoTaskBarIcon;

            ImGui::SetNextWindowClass( &window_class );
            ImGui::SetNextWindowSize( ImVec2( m_config.width, m_config.animated_height ), ImGuiCond_Always );

            struct style_guard {
                explicit style_guard( const panel_config_t& config ) noexcept {
                    ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, config.border_size );
                    ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, config.rounding );
                    ImGui::PushStyleColor( ImGuiCol_WindowBg, ImGui::ColorConvertU32ToFloat4( config.background_color ) );
                }
                ~style_guard() noexcept {
                    ImGui::PopStyleVar( 2 );
                    ImGui::PopStyleColor();
                }
            } guard{ m_config };

            ImGui::Begin( m_window_name.c_str(), &m_visible, ImGuiWindowFlags_NoDecoration );
        }

        void end_panel() noexcept {
            ImGui::End();
        }

    private:
        overlay_context& m_context;
        panel_config_t m_config;

        std::string m_window_name;
        bool m_visible;
    };

} // namespace feature::visual::overlay