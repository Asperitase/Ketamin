#ifndef FEATURE_OVERLAY_PARAMS_HPP
#define FEATURE_OVERLAY_PARAMS_HPP

#include <ImGui/imgui.h>

namespace feature::visual::overlay::panel {
    static constexpr auto width = 185;
    static constexpr auto height = 125;
    static constexpr auto border_size = 0;
    static constexpr auto rounding = 10;
    static constexpr auto bg_color = ImColor( 24, 23, 33, 255 );
} // namespace feature::visual::overlay::panel

namespace feature::visual::overlay::text {
    constexpr float text_pos_x = 20.f;
    constexpr float text_pos_y = 15.f;
    constexpr float sep_pos_y = text_pos_y + 30.f;
} // namespace feature::visual::overlay::text

#endif // !FEATURE_OVERLAY_PARAMS_HPP
