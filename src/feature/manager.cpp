#include "manager.hpp"

#include "feature/overlay/impl/overlay.hpp"

namespace feature {
    c_manager::c_manager() noexcept {
        add_class<feature::visual::overlay::overlay>( "Overlay" );
    }

    c_manager& c_manager::instance() noexcept {
        static c_manager instance;
        return instance;
    }

    template <typename T>
        requires std::is_default_constructible_v<T>
    void c_manager::add_class( const std::string_view& name ) noexcept {
        features.try_emplace( name, std::make_unique<T>() );
    }

    c_feature* c_manager::get_feature_by_name( const std::string_view& name ) const noexcept {
        auto it = features.find( name );
        return ( it != features.end() ) ? it->second.get() : nullptr;
    }

    std::shared_ptr<c_setting> c_manager::get_settings_by_feature( const std::string_view& name, const std::string_view& setting_name ) noexcept {
        auto feature = get_feature_by_name( name );
        if ( !feature )
            return nullptr;

        auto settings = feature->get_settings().get();

        return settings->get( setting_name.data() ).value();
    }

    void c_manager::update() const noexcept {
        for ( const auto& feature : features | std::views::values ) {
            if ( feature->is_enabled() ) {
                feature->on_enabled();
            } else {
                feature->on_disabled();
            }
        }
    }

    void c_manager::on_draw() const noexcept {
        for ( const auto& feature : features | std::views::values ) {
            if ( feature->is_enabled() ) {
                feature->on_draw();
            }
        }
    }

    void c_manager::on_menu() const noexcept {
        for ( const auto& category_raw : get_all_categories() ) {
            auto category = static_cast<category_t>( category_raw );
            if ( ImGui::BeginTabItem( category_to_string( category ).data() ) ) {
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
