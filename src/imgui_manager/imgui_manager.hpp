#pragma once

#include <atomic>

#include <window/render/directx11.hpp>

#include <imgui_manager/data.hpp>
#include <imgui_manager/settings.hpp>

class imgui_manager {
    using window_handle = HANDLE;

public:
    imgui_manager() noexcept = default;
    ~imgui_manager() noexcept;

    imgui_manager( const imgui_manager& ) = delete;
    imgui_manager& operator=( const imgui_manager& ) = delete;
    imgui_manager( imgui_manager&& ) = delete;
    imgui_manager& operator=( imgui_manager ) = delete;

    void initialize_imgui( window_handle handle, render::directx11* directx ) noexcept;

    void render_frame( menu_settings settings, render::directx11* directx ) noexcept;

    void shutdown_imgui() noexcept;

private:
    void configure_style() noexcept;

    void configure_imgui() noexcept;
    void load_fonts() const noexcept;

    void render_main_window( menu_settings settings ) noexcept;
    void render_other_window() noexcept;

private:
    std::atomic_flag initialize = ATOMIC_FLAG_INIT;
};