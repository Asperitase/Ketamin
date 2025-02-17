#include "modifier_module.hpp"

namespace weapon::modules {
    modifier_module::modifier_module( std::string_view name, float rate_modifier ) noexcept: module_base( name, rate_modifier ) { }

    float modifier_module::get_rate_modifier() const noexcept {
        return is_enabled() ? get_value() : 1.0f;
    }
} // namespace weapon::modules