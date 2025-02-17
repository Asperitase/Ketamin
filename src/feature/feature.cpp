#include "feature.hpp"

#include <cassert>

namespace feature {
    c_feature::c_feature( std::string name, std::string description, const category_t category ) noexcept
        : name( std::move( name ) ), description( std::move( description ) ), category( category ), settings{ std::make_unique<c_settings>() } {
        enabled_setting = settings->initialize( "Enabled", "Enables or disables this feature", false );
    }

    [[nodiscard]] bool c_feature::is_enabled() const noexcept {
        return std::any_cast<bool>( enabled_setting->get_value() );
    }

    [[nodiscard]] category_t c_feature::get_category() const noexcept {
        return category;
    }

    [[nodiscard]] std::unique_ptr<c_settings>& c_feature::get_settings() noexcept {
        return settings;
    }

    [[nodiscard]] const std::string& c_feature::get_name() const noexcept {
        return name;
    }

    [[nodiscard]] const std::string& c_feature::get_description() const noexcept {
        return description;
    }
} // namespace feature