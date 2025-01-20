#ifndef WEAPON_MODULE_NAME_ARRAY_HPP
#define WEAPON_MODULE_NAME_ARRAY_HPP

#include <constants/weapon_module_name.hpp>

namespace game_classes {
    static constexpr const char* modules_array[] = { module::NONE.data(),          module::LASER.data(), module::SILENCER.data(),
                                                     module::BOOST.data(),         module::BRAKE.data(), module::EXTENDEDMAGAZINE.data(),
                                                     module::GASCOMPRESSION.data() };
}

#endif // !WEAPON_MODULE_NAME_ARRAY_HPP
