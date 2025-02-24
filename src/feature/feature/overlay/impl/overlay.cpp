#pragma once

#include "overlay.hpp"
#include "imgui_helpers.hpp"
#include <algorithm>
#include <external/ImGui/imgui.h>

#include <utils/logger.hpp>

namespace feature::visual::overlay {
    overlay::impl::impl() noexcept {
        m_header_panel = std::make_unique<header_panel>( m_context, m_config, m_header_config );
        m_weapon_panel = std::make_unique<weapon_panel>( m_context, m_config );

        m_panels.reserve( 2 );
        m_panels.push_back( m_header_panel.get() );
        m_panels.push_back( m_weapon_panel.get() );
    }

    void overlay::impl::on_draw() noexcept {
        if ( !is_enabled() )
            return;

        if ( std::ranges::none_of( m_panels, []( const auto* panel ) {
                 return panel && panel->is_visible();
             } ) ) {
            return;
        }

        for ( auto* panel : m_panels ) {
            if ( panel ) {
                panel->render();
            }
        }
    }

    void overlay::impl::on_menu() noexcept {
        auto& manager = feature::c_manager::instance();

        if ( auto enabled = manager.get_settings_by_feature( "Overlay", "Enabled" ); enabled.get() ) [[likely]] {
            auto is_enabled = std::any_cast<bool>( enabled->get_value() );
            if ( ImGui::Checkbox( "Enable Overlay", &is_enabled ) ) {
                enabled->set_value( is_enabled );
            }
        }
    }

    void overlay::impl::on_enabled() noexcept {
        if ( !is_enabled() )
            return;

        std::ranges::for_each( m_panels, []( auto* panel ) {
            if ( panel ) {
                panel->set_visible( true );
            }
        } );
    }

    void overlay::impl::on_disabled() noexcept {
        if ( is_enabled() )
            return;

        std::ranges::for_each( m_panels, []( auto* panel ) {
            if ( panel ) {
                panel->set_visible( false );
            }
        } );
    }

    bool overlay::impl::is_enabled() const noexcept {
        auto& manager = feature::c_manager::instance();
        if ( auto enabled = manager.get_settings_by_feature( "Overlay", "Enabled" ); enabled.get() ) {
            return std::any_cast<bool>( enabled->get_value() );
        }
        return false;
    }

    overlay::overlay() noexcept: c_feature( "Overlay", "Renders a window displaying script selection options.", category_t::VISUAL ) {
        selected_weapon = settings->initialize( "selected_weapon", "Currently selected weapon in the game", 0 );
        selected_scope = settings->initialize( "selected_scope", "Currently selected scope in the game", 0 );
        selected_module = settings->initialize( "selected_module", "Currently selected module in the game", 0 );

        m_impl = std::make_unique<impl>();
    }

    void overlay::on_draw() noexcept {
        m_impl->on_draw();
    }

    void overlay::on_menu() noexcept {
        m_impl->on_menu();
    }

    void overlay::on_enabled() noexcept {
        m_impl->on_enabled();
    }

    void overlay::on_disabled() noexcept {
        m_impl->on_disabled();
    }

} // namespace feature::visual::overlay