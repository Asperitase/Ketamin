#ifndef MODULE_CONSTANTS_NAME_HPP
#define MODULE_CONSTANTS_NAME_HPP

#include <string_view>

namespace game_classes {
    namespace module {
        constexpr std::string_view NONE = "Empty";
        constexpr std::string_view LASER = "Laser";
        constexpr std::string_view SILENCER = "Silencer";
        constexpr std::string_view BOOST = "Muzzle Boost";
        constexpr std::string_view BRAKE = "Muzzle Brake";
        constexpr std::string_view EXTENDEDMAGAZINE = "Extended Magazine";
        constexpr std::string_view GASCOMPRESSION = "Compressor";
    }
} // namespace game_classes

#endif // !MODULE_CONSTANTS_NAME_HPP
