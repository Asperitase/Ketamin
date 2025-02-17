#pragma once

#include "render/directx11.hpp"
#include "window_constants.hpp"
#include <imgui_manager/imgui_manager.hpp>
#include <settings.hpp>

#include <memory>
#include <optional>
#include <span>
#include <Windows.h>

namespace window {

    class window final : imgui_manager {
        using atom = ATOM;
        using window_handle = std::optional<HWND>;

    public:
        window() noexcept;
        ~window() noexcept;

        window( const window& ) = delete;
        window& operator=( const window& ) = delete;
        window( window&& ) noexcept = default;
        window& operator=( window&& ) noexcept = default;

        [[nodiscard]] static std::unique_ptr<window> create() noexcept;
        void shutdown() noexcept;
        [[nodiscard]] bool create_window_handle() noexcept;
        void render_loop( const app_settings& settings ) noexcept;
        [[nodiscard]] window_handle get_handle() const noexcept;

    private:
        void process_window_messages() noexcept;
        bool initialize_window_class() noexcept;
        bool register_window_class() noexcept;

        window_handle handle = nullptr;
        WNDCLASSEX window_class{};
        bool is_running = false;
    };

} // namespace window