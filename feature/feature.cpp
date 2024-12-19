#include "feature.hpp"

#include <cassert>
#include <syscall.hpp>

namespace feature {
    [[nodiscard]] std::string_view feature_type_to_string( category_t category ) noexcept {
        switch ( category ) {
        case category_t::CONTROL:
            return "Control";
        case category_t::SETTINGS:
            return "Settings";
        case category_t::APPEARANCE:
            return "Appearance";
        [[unlikely]] default:
            return "Unknown";
        }
    }

    c_feature::c_feature( std::string_view name, std::string_view description, const category_t category ) noexcept
        : name( name ), description( description ), category( category ), settings_{ std::make_unique<c_settings>() },
          enabled_setting{ std::make_shared<c_setting>( "Enabled", "Enables or disables this feature", false ) } {
        settings_->add_settings( enabled_setting );
    }

    [[nodiscard]] bool c_feature::is_enabled() const noexcept {
        return std::get<bool>( enabled_setting->get_value() );
    }

    [[nodiscard]] category_t c_feature::get_category() const noexcept {
        return category;
    }

    [[nodiscard]] std::unique_ptr<c_settings>& c_feature::get_settings() noexcept {
        return settings_;
    }

    [[nodiscard]] const std::string_view c_feature::get_name() const noexcept {
        return name;
    }

    [[nodiscard]] const std::string_view c_feature::get_description() const noexcept {
        return description;
    }
} // namespace feature