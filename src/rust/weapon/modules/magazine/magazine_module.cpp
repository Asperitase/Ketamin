#include "magazine_module.hpp"

namespace weapon::modules {

    magazine_module::magazine_module( std::string_view name, int additional_ammo ) noexcept
        : module_base( name, std::min( additional_ammo, max_additional_ammo ) ) { }

    int magazine_module::get_additional_ammo() const noexcept {
        return is_enabled() ? get_value() : 0;
    }

    weapon::core::module_type magazine_module::get_type() const noexcept {
        return weapon::core::module_type::magazine;
    }

} // namespace weapon::modules