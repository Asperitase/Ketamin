#ifndef MENU_HPP
#define MENU_HPP

#include <memory>

#include "menu_params.hpp"

namespace menu {

    class c_menu : menu_data_t {
    public:
        c_menu() noexcept = default;
        ~c_menu() noexcept = default;
        c_menu( const c_menu& ) = delete;
        c_menu& operator=( const c_menu& ) = delete;
        c_menu( c_menu&& ) = delete;
        c_menu& operator=( c_menu&& ) = delete;

        void render() const noexcept;
    };

} // namespace menu

#endif // !MENU_HPP
