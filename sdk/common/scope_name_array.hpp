#ifndef WEAPON_SCOPE_NAME_ARRAY_HPP
#define WEAPON_SCOPE_NAME_ARRAY_HPP

#include <constants/weapon_scope_name.hpp>

namespace game_classes {
    static constexpr const char* scopes_array[] = { scope::NONE.data(), scope::SIMPLE.data(), scope::HOLOSIGHT.data(), scope::X8.data(),
                                                    scope::X16.data() };
}

#endif // !WEAPON_SCOPE_NAME_ARRAY_HPP
