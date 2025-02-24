#pragma once

#include <external/ImGui/imgui.h>
#include <string_view>

namespace feature::visual::overlay {
    enum class update_overlay_slot_flags {
        weapon,
        scope,
        module
    };

    struct weapon_display_config_t {
        ImColor text_color{ 249, 249, 250, 255 };
        float vertical_spacing{ 20.0f };

        static constexpr float default_x{ 20.0f };
        static constexpr float default_y{ 15.0f };
        static constexpr float separator_offset_y{ 30.0f };

        float x{ default_x };
        float y{ default_y };

        [[nodiscard]] constexpr float get_separator_y() const noexcept {
            return y + separator_offset_y;
        }
    };

    struct header_config_t {
        ImColor text_color{ 206, 206, 222, 255 };
        ImColor icon_color{ 206, 206, 222, 255 };
        std::string_view title{ "Weapon Selected" };
        std::string_view icon{ "E" };
        float icon_offset{ 130.0f };
    };

    struct panel_config_t {
        float width{ 185.0f };
        float height{ 125.0f };
        float animated_height{ 0.f };
        float border_size{ 0.0f };
        float rounding{ 10.0f };
        ImColor background_color{ 24, 23, 33, 255 };
    };

} // namespace feature::visual::overlay