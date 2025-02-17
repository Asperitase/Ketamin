#pragma once
#include <rust/weapon/weapons/base/weapon_base.hpp>

namespace weapon {

    class rifle final : public weapon_base {
    public:
        explicit rifle( std::string_view name, size_t base_ammo, float fire_rate ) noexcept;

        ~rifle() noexcept override = default;

        [[nodiscard]] core::weapon_type get_type() const noexcept override;
    };

} // namespace weapon