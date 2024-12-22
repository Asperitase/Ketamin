#include "manager.hpp"

#include "control/control.hpp"
#include "overlay/overlay.hpp"

#include <cassert>
#include <ranges>

namespace feature {
    c_manager::c_manager() noexcept {
        add_feature<feature::menu::control::c_control>( "Control" );
        add_feature<feature::visual::overlay::c_overlay>( "Overlay" );
    }

    [[nodiscard]] c_manager& c_manager::instance() noexcept {
        static c_manager instance;
        return instance;
    }

    template <typename T>
    void c_manager::add_feature( const std::string_view& name ) noexcept {
        features.emplace( name, std::make_unique<T>() );
    }

    [[nodiscard]] const std::unordered_map<std::string_view, std::unique_ptr<c_feature>>& c_manager::get_feature() const noexcept {
        return features;
    }

    [[nodiscard]] c_feature* c_manager::get_feature_by_name( const std::string_view& name ) const noexcept {
        const auto& feature = features.at( name );
        return feature.get();
    }

    void c_manager::on_draw() const noexcept {
        for ( const auto& feature : features | std::views::values ) {
            if ( feature->is_enabled() )
                feature->on_draw();
        }
    }

    void c_manager::on_menu() const noexcept {
        for ( const auto& category_raw : get_all_categories() ) {
            auto category = static_cast<category_t>( category_raw );
            if ( ImGui::BeginTabItem( feature_type_to_string( category ).data() ) ) {
                for ( const auto& feature : features | std::views::values | std::views::filter( [category]( const auto& filter ) {
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
} // namespace feature