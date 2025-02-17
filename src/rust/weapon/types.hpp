#pragma once

namespace weapon::core {

    enum class weapon_type {
        rifle,
        semi,
        smg,
        pistol,
        sniper,
        shotgun,
        other
    };

    enum class module_type {
        laser,
        silencer,
        boost,
        brake,
        magazine,
        suppressor
    };

} // namespace weapon::core