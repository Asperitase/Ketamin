#ifndef IMGUI_MANAGER_HPP
#define IMGUI_MANAGER_HPP

#include <d3d/directx.hpp>

#include "menu.hpp"

#include <atomic>

namespace render {
    class c_imgui_manager : public menu::c_menu {
        using window_handle = HANDLE;

    public:
        c_imgui_manager() noexcept = default;
        ~c_imgui_manager() noexcept;

        c_imgui_manager( const c_imgui_manager& ) = delete;
        c_imgui_manager& operator=( const c_imgui_manager& ) = delete;
        c_imgui_manager( c_imgui_manager&& ) = delete;
        c_imgui_manager& operator=( c_imgui_manager ) = delete;

        void initialize_imgui( window_handle handle, c_directx* directx ) noexcept;

        void render_imgui_frame( c_directx* directx ) noexcept;

        void shutdown_imgui() noexcept;

    private:
        void configure_style() noexcept;

        void load_fonts() const noexcept;

    private:
        std::atomic_flag initialize = ATOMIC_FLAG_INIT;
    };
} // namespace render

#endif // !IMGUI_MANAGER_HPP
