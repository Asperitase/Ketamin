#ifndef WEAPON_CONSTANTS_NAME_HPP
#define WEAPON_CONSTANTS_NAME_HPP

#include <string_view>

namespace game_classes {
    namespace rifle {
        constexpr std::string_view AK = "Assault Rifle";
        constexpr std::string_view HMLMG = "Hmlmg";
        constexpr std::string_view HANDMADE_SMG = "Handmade SMG";
        constexpr std::string_view CUSTOM_SMG = "Custom SMG";
        constexpr std::string_view LR300 = "Lr300";
        constexpr std::string_view M249 = "M249";
        constexpr std::string_view THOMPSON = "Thompson";
        constexpr std::string_view MP5A4 = "Mp5a4";
        constexpr std::string_view MINIGUN = "Minigun";
    } // namespace rifle

    namespace semi {
        constexpr std::string_view SAR = "Semi Automatic Rifle";
        constexpr std::string_view SKS = "Sks";
        constexpr std::string_view M39 = "M39";
    } // namespace semi

    namespace pistol {
        constexpr std::string_view M92 = "M92";
        constexpr std::string_view PROTOTYPE17 = "Prototype 17";
        constexpr std::string_view PYTHON_REVOLVER = "Python Revolver";
        constexpr std::string_view SAP = "Semi Automatic Pistol";
        constexpr std::string_view HIGH_CALIBER_REVOLVER = "High Caliber Revolver";
    } // namespace pistol

    namespace shotgun {
        constexpr std::string_view SPAS12 = "Spas 12 Shotgun";
        constexpr std::string_view PUMP_SHOTGUN = "Pump Shotgun";
        constexpr std::string_view M4 = "M4";
        constexpr std::string_view DBS = "Double Barrel Shotgun";
    } // namespace shotgun

    namespace sniper {
        constexpr std::string_view BOLT = "Bolt Action Rifle";
        constexpr std::string_view L96 = "L96";

    } // namespace sniper

    namespace other {
        constexpr std::string_view EOKA = "Eoka";
        constexpr std::string_view MGL = "Multiple Grenade Launcher";
        constexpr std::string_view NAILGUN = "Nailgun";
    } // namespace other
} // namespace game_classes

#endif // !WEAPON_CONSTANTS_NAME_HPP
