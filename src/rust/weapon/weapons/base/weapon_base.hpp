#pragma once
#include <memory>
#include <rust/weapon/modules/base/module_container.hpp>

namespace weapon {

    class weapon_base {
    public:
        explicit weapon_base( std::string_view name, size_t base_ammo, float fire_rate ) noexcept;
        virtual ~weapon_base() = default;

        [[nodiscard]] std::string_view get_name() const noexcept;
        [[nodiscard]] size_t get_base_ammo() const noexcept;

        [[nodiscard]] float get_fire_rate() const noexcept;
        [[nodiscard]] virtual core::weapon_type get_type() const noexcept = 0;

        template <typename T>
        void add_module( std::unique_ptr<T> module );

        template <typename T>
        [[nodiscard]] T* get_module( std::string_view name ) const noexcept;

    private:
        std::string_view m_name;
        size_t m_base_ammo;
        float m_fire_rate;

        modules::module_container m_modules;
    };

} // namespace weapon