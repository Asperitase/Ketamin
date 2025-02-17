#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

#include "overlay_config.hpp"

// TODO
static constexpr const char* weapons_array[] = { "none", "ak47" };
static constexpr const char* scopes_array[] = { "none" };
static constexpr const char* modules_array[] = { "none" };

namespace feature::visual::overlay {
    struct weapon_data_t {
        std::optional<std::string_view> name;
        std::optional<std::string_view> scope;
        std::optional<std::string_view> module;

        constexpr bool is_valid() const noexcept {
            return !name.value().empty();
        }
    };

} // namespace feature::visual::overlay