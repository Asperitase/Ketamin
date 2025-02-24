#pragma once

#include <concepts>
#include <limits>
#include <type_traits>

template <typename Flag, std::integral type>
    requires std::is_enum_v<Flag>
class bit_flags {
public:
    template <Flag flag>
    constexpr void set() noexcept {
        flags |= to_mask<flag>();
    }

    template <Flag flag>
    constexpr void unset() noexcept {
        flags &= ~to_mask<flag>();
    }

    template <Flag flag>
    [[nodiscard]] constexpr bool has() const noexcept {
        return ( flags & to_mask<flag>() ) != 0;
    }

    [[nodiscard]] explicit constexpr operator bool() const noexcept {
        return flags != 0;
    }

private:
    template <Flag flag>
    static constexpr auto to_mask() noexcept {
        static_assert( static_cast<std::underlying_type_t<Flag>>( flag ) >= 0 );
        static_assert( static_cast<std::underlying_type_t<Flag>>( flag ) < std::numeric_limits<type>::digits );
        return 1 << static_cast<std::underlying_type_t<Flag>>( flag );
    }

    type flags{ 0 };
};