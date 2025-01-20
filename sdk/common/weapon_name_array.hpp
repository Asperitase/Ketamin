#ifndef WEAPON_NAME_ARRAY_HPP
#define WEAPON_NAME_ARRAY_HPP

#include <constants/weapon_name.hpp>

namespace game_classes {
    static constexpr const char* weapons_array[] = { weapon::NONE.data(),        rifle::AK.data(),
                                                     rifle::HMLMG.data(),        rifle::HANDMADE_SMG.data(),
                                                     rifle::CUSTOM_SMG.data(),   rifle::LR300.data(),
                                                     rifle::M249.data(),         rifle::THOMPSON.data(),
                                                     rifle::MP5A4.data(),        rifle::MINIGUN.data(),
                                                     semi::SAR.data(),           semi::SKS.data(),
                                                     semi::M39.data(),           pistol::M92.data(),
                                                     pistol::PROTOTYPE17.data(), pistol::PYTHON_REVOLVER.data(),
                                                     pistol::SAP.data(),         pistol::HIGH_CALIBER_REVOLVER.data(),
                                                     shotgun::SPAS12.data(),     shotgun::PUMP_SHOTGUN.data(),
                                                     shotgun::M4.data(),         shotgun::DBS.data(),
                                                     sniper::BOLT.data(),        sniper::L96.data(),
                                                     other::EOKA.data(),         other::MGL.data(),
                                                     other::NAILGUN.data() };
}

#endif // !WEAPON_NAME_ARRAY_HPP
