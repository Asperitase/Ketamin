#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "d3d/directx.hpp"

#include "../menu/imgui_manager.hpp"

#include <memory>
#include <optional>
#include <Windows.h>

namespace render {
    constexpr const char* WINDOW_CLASS_NAME = "UnityWndClass";
    constexpr const char* WINDOW_NAME = "Rust";

    class c_window final : c_imgui_manager {
        using window_handle = std::optional<HWND>;
        using atom = ATOM;

    public:
        explicit c_window() noexcept;
        [[nodiscard]] static std::unique_ptr<c_window> create() noexcept;

        c_window( const c_window& ) = delete;
        c_window& operator=( const c_window& ) = delete;
        c_window( c_window&& ) = delete;
        c_window& operator=( c_window&& ) = delete;

        ~c_window() noexcept;
        void reset() noexcept;

        void create_window_handle() noexcept;
        void render_loop() noexcept;

    private:
        window_handle handle = nullptr;
        WNDCLASSEX window_class_t;
    };
} // namespace render

#endif // !WINDOW_HPP
