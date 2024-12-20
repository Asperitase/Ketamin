#ifndef WEAPON_NAME_SELECTOR_HPP
#define WEAPON_NAME_SELECTOR_HPP

#include <constants/weapon_name.hpp>

#include <vector>

static const char* weapons_array[] = { game_classes::rifle::AK.data(),
                                game_classes::rifle::HMLMG.data(),
                                game_classes::rifle::HANDMADE_SMG.data(),
                                game_classes::rifle::CUSTOM_SMG.data(),
                                game_classes::rifle::LR300.data(),
                                game_classes::rifle::M249.data(),
                                game_classes::rifle::THOMPSON.data(),
                                game_classes::rifle::MP5A4.data(),
                                game_classes::rifle::MINIGUN.data(),
                                game_classes::semi::SAR.data(),
                                game_classes::semi::SKS.data(),
                                game_classes::semi::M39.data(),
                                game_classes::pistol::M92.data(),
                                game_classes::pistol::PROTOTYPE17.data(),
                                game_classes::pistol::PYTHON_REVOLVER.data(),
                                game_classes::pistol::SAP.data(),
                                game_classes::pistol::HIGH_CALIBER_REVOLVER.data(),
                                game_classes::shotgun::SPAS12.data(),
                                game_classes::shotgun::PUMP_SHOTGUN.data(),
                                game_classes::shotgun::M4.data(),
                                game_classes::shotgun::DBS.data(),
                                game_classes::sniper::BOLT.data(),
                                game_classes::sniper::L96.data(),
                                game_classes::other::EOKA.data(),
                                game_classes::other::MGL.data(),
                                game_classes::other::NAILGUN.data() };

#endif // !WEAPON_NAME_SELECTOR_HPP
