#pragma once
#include <rust/weapon/modules/base/base_module.hpp>
#include <rust/weapon/modules/name.hpp>
#include <string>
#include <unordered_map>

namespace weapon::modules {

    class modifier_module final : public module_base<float> {
    public:
        explicit modifier_module( std::string_view name, float rate_modifier = 1.0f ) noexcept;

        [[nodiscard]] float get_rate_modifier() const noexcept;
    };

} // namespace weapon::modules