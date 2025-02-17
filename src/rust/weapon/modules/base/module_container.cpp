#pragma once
#include "module_container.hpp"
#include <ranges>

#include <rust/weapon/modules/magazine/magazine_module.hpp>
#include <rust/weapon/modules/modifier_module/modifier_module.hpp>

namespace weapon::modules {

    template <typename T>
    void module_container::add_module( std::unique_ptr<T> module ) {
        static_assert( std::is_base_of_v<modules::i_module, T>, "Module must inherit from i_module" );

        const auto existing_module = std::ranges::find_if( m_modules, [module_name = module->get_name()]( const auto& existing ) {
            return existing->get_name() == module_name;
        } );

        if ( existing_module != m_modules.end() ) {
            *existing_module = std::move( module );
            return;
        }

        m_modules.push_back( std::move( module ) );
    }

    template <typename T>
    [[nodiscard]] T* module_container::get_module( std::string_view name ) const noexcept {
        auto it = std::ranges::find_if( m_modules, [name]( const auto& module ) {
            return module->get_name() == name;
        } );

        return it != m_modules.end() ? dynamic_cast<T*>( it->get() ) : nullptr;
    }

    [[nodiscard]] bool module_container::has_modules() const noexcept {
        return !m_modules.empty();
    }

    void module_container::clear() noexcept {
        m_modules.clear();
    }

    template void module_container::add_module<modules::modifier_module>( std::unique_ptr<modules::modifier_module> );
    template modules::modifier_module* module_container::get_module<modules::modifier_module>( std::string_view ) const noexcept;

    template void module_container::add_module<modules::magazine_module>( std::unique_ptr<modules::magazine_module> );
    template modules::magazine_module* module_container::get_module<modules::magazine_module>( std::string_view ) const noexcept;

} // namespace weapon::modules