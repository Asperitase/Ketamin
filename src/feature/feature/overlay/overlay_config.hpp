#pragma once

#include <array>

namespace feature::visual::overlay {
    struct weapon_display_config_t {
        ImColor text_color{ 249, 249, 250, 255 };
        float vertical_spacing{ 20.0f };
    };

    struct header_config_t {
        std::array<float, 4> text_color{ 206 / 255.0f, 206 / 255.0f, 222 / 255.0f, 1.0f };
        std::array<float, 4> icon_color{ 206 / 255.0f, 206 / 255.0f, 222 / 255.0f, 1.0f };
        std::string_view title{ "Weapon Selected" };
        std::string_view icon{ "E" };
        float icon_offset{ 130.0f };
    };

    struct panel_config_t {
        float width{ 185.0f };
        float height{ 125.0f };
        float border_size{ 0.0f };
        float rounding{ 10.0f };

        std::array<float, 4> background_color{ 24.0f / 255.0f, 23.0f / 255.0f, 33.0f / 255.0f, 1.0f };

        constexpr bool operator==( const panel_config_t& ) const noexcept = default;
    };

    struct text_position_t {
        static constexpr float default_x{ 20.0f };
        static constexpr float default_y{ 15.0f };
        static constexpr float separator_offset_y{ 30.0f };

        float x{ default_x };
        float y{ default_y };

        [[nodiscard]] constexpr float get_separator_y() const noexcept {
            return y + separator_offset_y;
        }
    };
} // namespace feature::visual::overlay