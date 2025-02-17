#pragma once
#include "base_module.hpp"
#include <memory>
#include <vector>

namespace weapon::modules {

    class module_container {
    public:
        module_container() noexcept = default;

        template <typename T>
        void add_module( std::unique_ptr<T> module );

        template <typename T>
        [[nodiscard]] T* get_module( std::string_view name ) const noexcept;

        [[nodiscard]] bool has_modules() const noexcept;
        void clear() noexcept;

    private:
        std::vector<std::unique_ptr<modules::i_module>> m_modules;
    };

} // namespace weapon::modules