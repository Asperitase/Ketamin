#ifndef MENU_HPP
#define MENU_HPP

#include <memory>

#include "../feature/manager.hpp"

namespace menu {

    struct menu_data_t {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        int width = 600;
        int height = 300;
    };

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
