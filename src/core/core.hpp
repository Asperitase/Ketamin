#pragma once

#include <settings.hpp>
#include <utils/mouse/mouse.hpp>
#include <utils/result_error.hpp>
#include <window/window.hpp>

namespace core {

    class launcher final {
    public:
        launcher() noexcept = default;
        ~launcher() noexcept = default;

        launcher( const launcher& ) = delete;
        launcher& operator=( const launcher& ) = delete;
        launcher( launcher&& ) = delete;
        launcher& operator=( launcher&& ) = delete;

        [[nodiscard]] static launcher& instance() noexcept;

        [[nodiscard]] result<bool> initialize_syscalls() const noexcept;
        [[nodiscard]] result<bool> create_window( const std::unique_ptr<window::window>& window ) const noexcept;
        [[nodiscard]] result<bool> initialize_mouse() const noexcept;

        [[nodiscard]] result<bool> start( const std::unique_ptr<window::window>& window ) const noexcept;

        [[nodiscard]] int shutdown( result<bool> status ) noexcept;
        [[nodiscard]] const app_settings& get_settings() const noexcept;

    private:
        mouse::mouse& mouse = mouse::mouse::instance();
        app_settings settings_{};
    };

} // namespace core