#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "feature.hpp"

#include <unordered_map>

namespace feature {
    class c_manager final {
    public:
        c_manager() noexcept;
        ~c_manager() noexcept;
        c_manager( const c_manager& ) = delete;
        c_manager& operator=( const c_manager& ) = delete;
        c_manager( c_manager&& ) = delete;
        c_manager& operator=( c_manager&& ) = delete;

        [[nodiscard]] static std::unique_ptr<c_manager> create() noexcept;

    public:
        [[nodiscard]] const std::unordered_map<std::string_view, c_feature*>& get_feature() const noexcept;
        [[nodiscard]] c_feature* get_feature_by_name( const std::string_view& name ) const noexcept;

        void on_draw() const noexcept;
        void on_menu() const noexcept;

    private:
        void add_feature( const std::string_view& name, c_feature* feature ) noexcept;

        std::unordered_map<std::string_view, c_feature*> features;
    };
} // namespace feature

#endif // !MANAGER_HPP
