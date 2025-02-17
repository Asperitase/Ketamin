#pragma once

#include "overlay.hpp"
#include <algorithm>
#include <external/ImGui/imgui.h>

namespace feature::visual::overlay {
    overlay::impl::impl( const config_t& config ) noexcept: m_context{} {
        m_context.init( config.weapon, config.scope, config.module );

        m_header_panel = std::make_unique<c_header_panel>();
        m_weapon_panel = std::make_unique<c_weapon_panel>( m_context );

        m_panels.reserve( 1 );
        m_panels.push_back( m_header_panel.get() );
        m_panels.push_back( m_weapon_panel.get() );

        m_enabled = config.enabled;
        m_weapon = config.weapon;
        m_scope = config.scope;
        m_module = config.module;
    }

    void overlay::impl::draw() noexcept {
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

    void overlay::impl::show_menu() noexcept {
        auto enabled = is_enabled();
        if ( ImGui::Checkbox( "Enable Overlay", &enabled ) ) {
            m_enabled->set_value( enabled );
        }

        static int weapon = std::any_cast<int>( m_weapon->get_value() );
        if ( ImGui::Combo( "Weapon", &weapon, weapons_array, IM_ARRAYSIZE( weapons_array ) ) ) {
            m_weapon->set_value( weapon );
        }
    }

    void overlay::impl::enable() noexcept {
        if ( !is_enabled() )
            return;

        std::ranges::for_each( m_panels, []( auto* panel ) {
            if ( panel ) {
                panel->set_visible( true );
            }
        } );
    }

    void overlay::impl::disable() noexcept {
        if ( is_enabled() )
            return;

        std::ranges::for_each( m_panels, []( auto* panel ) {
            if ( panel ) {
                panel->set_visible( false );
            }
        } );
    }

    [[nodiscard]] bool overlay::impl::is_enabled() const noexcept {
        if ( auto enabled = m_enabled; enabled ) {
            return std::any_cast<bool>( enabled->get_value() );
        }
        return false;
    }

    overlay::overlay() noexcept: c_feature( "Overlay", "Renders a window displaying script selection options.", category_t::VISUAL ) {
        selected_weapon = settings->initialize( "overlay.selected_weapon", "Currently selected weapon in the game", 0 );
        selected_scope = settings->initialize( "overlay.selected_scope", "Currently selected scope in the game", 0 );
        selected_module = settings->initialize( "overlay.selected_module", "Currently selected module in the game", 0 );

        impl::config_t config{ .weapon = selected_weapon, .scope = selected_scope, .module = selected_module, .enabled = enabled_setting };

        m_impl = std::make_unique<impl>( config );
    }

    void overlay::on_draw() noexcept {
        m_impl->draw();
    }

    void overlay::on_menu() noexcept {
        m_impl->show_menu();
    }

    void overlay::on_enabled() noexcept {
        m_impl->enable();
    }

    void overlay::on_disabled() noexcept {
        m_impl->disable();
    }

} // namespace feature::visual::overlay