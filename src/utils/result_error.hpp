#pragma once

#include <string_view>
#include <variant>

namespace core {

    template <typename T>
    class result {
    public:
        struct error_t {
            bool code;
            std::string_view message;
        };

        constexpr result( T&& value ) noexcept: value_( std::move( value ) ) { }
        constexpr result( const error_t& error ) noexcept: value_( error ) { }

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
} // namespace core