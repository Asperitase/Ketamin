#pragma once

#include <string_view>
#include <variant>

// Reference:
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55#:~:text=STATUS_DEVICE_NOT_CONNECTED
#define STATUS_DEVICE_NOT_CONNECTED static_cast<std::int32_t>( 0xC000009D )

namespace mouse {
    template <typename T>
    class result {
        using NTSTATUS = std::int32_t;

    public:
        struct error_t {
            NTSTATUS code;
            std::string_view message;
        };

        // Constructors
        constexpr result( T&& value ) noexcept: value_( std::move( value ) ) { }
        constexpr result( const error_t& error ) noexcept: value_( error ) { }

        // Accessors
        [[nodiscard]] constexpr bool is_success() const noexcept {
            return std::holds_alternative<T>( value_ );
        }

        [[nodiscard]] constexpr const T& value() const& noexcept {
            return std::get<T>( value_ );
        }

        [[nodiscard]] constexpr const error_t& error() const& noexcept {
            return std::get<error_t>( value_ );
        }

    private:
        std::variant<T, error_t> value_;
    };
} // namespace mouse