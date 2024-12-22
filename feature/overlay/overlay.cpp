#include "overlay.hpp"

#include <ImGui/imgui_data.hpp>

#include "overlay/overlay_panel.hpp"

namespace feature::visual::overlay {
    c_overlay::c_overlay() noexcept: c_feature( "Overlay", "Renders a window displaying script selection options.", category_t::VISUAL ) { }

    void c_overlay::on_draw() noexcept {
        create_overlay_panel( []( overlay_context_t& context ) {
            context.update();
        } );
    }

    void c_overlay::on_menu() noexcept {
        ImGui::Checkbox( "Enable Overlay", &std::get<bool>( enabled_setting->get_value() ) );
    }
} // namespace feature::visual::overlay