#pragma once
#include <rust/weapon/modules/base/base_module.hpp>

namespace weapon::modules {

    class magazine_module final : public module_base<int> {
    public:
        explicit magazine_module( std::string_view name, int additional_ammo ) noexcept;

        [[nodiscard]] int get_additional_ammo() const noexcept;
        [[nodiscard]] weapon::core::module_type get_type() const noexcept;

    private:
        static constexpr int max_additional_ammo = 10;
    };

} // namespace weapon::modules