#ifndef WEAPON_MODULE_NAME_ARRAY_HPP
#define WEAPON_MODULE_NAME_ARRAY_HPP

#include <constants/weapon_module_name.hpp>

static const char* modules_array[] = { game_classes::module::NONE.data(),          game_classes::module::LASER.data(),
                                       game_classes::module::SILENCER.data(),      game_classes::module::BOOST.data(),
                                       game_classes::module::BRAKE.data(),         game_classes::module::EXTENDEDMAGAZINE.data(),
                                       game_classes::module::GASCOMPRESSION.data() };

#endif // !WEAPON_MODULE_NAME_ARRAY_HPP
