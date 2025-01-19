#ifndef FEATURE_CONTROL_CONTEXT_HPP
#define FEATURE_CONTROL_CONTEXT_HPP

#include <string_view>

#include <manager.hpp>

namespace feature::control {
    [[nodiscard]] auto get_feature( const std::string_view func ) noexcept {
        const auto& feature = feature::c_manager::instance().get_feature_by_name( func );
        return feature;
    }

    [[nodiscard]] auto get_params( const std::string_view func, const std::string_view name ) noexcept {
        const auto& parameter = get_feature( func )->get_settings()->get( name.data() );
        return parameter.get();
    }
} // namespace feature::menu::control

#endif // !FEATURE_CONTROL_CONTEXT_HPP
