#pragma once
#include <rust/weapon/types.hpp>
#include <string_view>
#include <concepts>

namespace weapon::modules {

    namespace core {
        template <typename T> concept ModuleValue = std::same_as<T, float> || std::same_as<T, int>;
    }

    class i_module {
    public:
        virtual ~i_module() = default;
        [[nodiscard]] virtual std::string_view get_name() const noexcept = 0;
        [[nodiscard]] virtual bool is_enabled() const noexcept = 0;
        virtual void set_enabled( bool state ) noexcept = 0;
    };

    template <core::ModuleValue T>
    class module_base : public i_module {
    public:
        explicit module_base( std::string_view name, T value ) noexcept;

        [[nodiscard]] std::string_view get_name() const noexcept override;
        [[nodiscard]] bool is_enabled() const noexcept override;
        void set_enabled( bool state ) noexcept override;

        [[nodiscard]] T get_value() const noexcept;
        void set_value( T value ) noexcept;

    private:
        std::string_view m_name;
        T m_value;
        bool m_enabled;
    };

} // namespace weapon::modules