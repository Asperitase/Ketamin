#include "manager.hpp"

#include "control/control.hpp"
#include "control/control_punch.hpp"
#include "overlay/overlay.hpp"

#include <cassert>
#include <ranges>

namespace feature {
    c_manager::c_manager() noexcept {
        add_class<feature::control::c_control_punch>( "ControlPunch" );

        add_class<feature::menu::control::c_control>( "Control" );
        add_class<feature::visual::overlay::c_overlay>( "Overlay" );
    }

    [[nodiscard]] c_manager& c_manager::instance() noexcept {
        static c_manager instance;
        return instance;
    }

    template <typename T>
        requires std::is_default_constructible_v<T>
    void c_manager::add_class( const std::string_view& name ) noexcept {
        klass.emplace( name, std::make_unique<T>() );
    }

    [[nodiscard]] const std::unordered_map<std::string_view, std::unique_ptr<c_feature>>& c_manager::get_alL_class() const noexcept {
        return klass;
    }

    [[nodiscard]] c_feature* c_manager::get_class_by_name( const std::string_view& name ) const noexcept {
        const auto& feature = klass.at( name );
        return feature.get();
    }

    void c_manager::update() const noexcept {
        for ( const auto& feature : klass | std::views::values ) {
            if ( feature->is_enabled() )
                feature->on_enabled();
            else
                feature->on_disabled();
        }
    }

    void c_manager::on_draw() const noexcept {
        for ( const auto& feature : klass | std::views::values ) {
            if ( feature->is_enabled() )
                feature->on_draw();
        }
    }

    void c_manager::on_menu() const noexcept {
        for ( const auto& category_raw : get_all_categories() ) {
            auto category = static_cast<category_t>( category_raw );
            if ( ImGui::BeginTabItem( feature_type_to_string( category ).data() ) ) {
                for ( const auto& feature : klass | std::views::values | std::views::filter( [category]( const auto& filter ) {
                                                return filter->get_category() == category;
                                            } ) ) {
                    ImGui::Text( "%s", feature->get_name().data() );
                    ImGui::TextColored( ImColor( 173, 173, 173, 255 ), "%s", feature->get_description().data() );

                    feature->on_menu();

                    ImGui::Separator();
                }
                ImGui::EndTabItem();
            }
        }
    }

        [[nodiscard]] c_feature* manager::get_class( const std::string_view methods ) noexcept {
            return c_manager::instance().get_class_by_name( methods );
        }

        [[nodiscard]] std::shared_ptr<c_setting> manager::get_parameters_from_class( const std::string_view methods,                                                                                     const std::string_view name ) noexcept {
            auto feature = manager::get_class( methods );
            if ( !feature )
                return nullptr;

            auto settings = feature->get_settings().get();
            if ( !settings )
                return nullptr;

            return settings->get( std::string( name ) );
        }
} // namespace feature