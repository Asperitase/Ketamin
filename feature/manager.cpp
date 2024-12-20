#include "manager.hpp"

#include "watermark/watermark.hpp"
#include "overlay/overlay.hpp"
#include "control/control.hpp"

#include <cassert>
#include <ranges>

namespace feature {
    c_manager::c_manager() noexcept {
        features = std::unordered_map<std::string_view, c_feature*>();

        add_feature( "Watermark", new feature::visual::watermark::c_watermark() );
        add_feature( "Overlay", new feature::visual::overlay::c_overlay() );
        add_feature( "Control", new feature::visual::control::c_control() );
    }

    c_manager::~c_manager() noexcept {
        features.clear();

        for ( const auto& feature : features | std::views::values )
            delete feature;
    }

    [[nodiscard]] std::unique_ptr<c_manager> c_manager::create() noexcept {
        return std::make_unique<c_manager>();
    }

    void c_manager::add_feature( const std::string_view& name, c_feature* feature ) noexcept {
        features.emplace( name, std::move( feature ) );
    }

    [[nodiscard]] const std::unordered_map<std::string_view, c_feature*>& c_manager::get_feature() const noexcept {
        return features;
    }

    [[nodiscard]] c_feature* c_manager::get_feature_by_name( const std::string_view& name ) const noexcept {
        return features.at( name );
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
            const auto category_name = feature_type_to_string( category );

            if ( ImGui::BeginTabItem( category_name.data() ) ) {
                for ( const auto& feature : features | std::views::values | std::views::filter( [category]( const auto& filter ) {
                                                return filter->get_category() == category;
                                            } ) ) {

                    if ( feature->draw_section ) {
                        ImGui::Text( "%s", feature->get_name().data() );
                        ImGui::TextColored( ImColor( 173, 173, 173, 255 ), "%s", feature->get_description().data() );
                    }

                    feature->on_menu();

                    if ( feature->draw_section )
                        ImGui::Separator();
                }
                ImGui::EndTabItem();
            }
        }
    }
} // namespace feature