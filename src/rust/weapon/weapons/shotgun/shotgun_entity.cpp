#include "shotgun_entity.hpp"

namespace weapon {

    shotgun::shotgun( std::string_view name, size_t base_ammo, float fire_rate ) noexcept: weapon_base( name, base_ammo, fire_rate ) { }

    core::weapon_type shotgun::get_type() const noexcept {
        return core::weapon_type::shotgun;
    }

} // namespace weapon