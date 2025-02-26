#include "imgui_manager.hpp"

#include <external/resources/font/Glory.hpp>
#include <external/resources/font/GloryBold.hpp>
#include <external/resources/icon/icons.hpp>

#include <utils/random_string.hpp>

#include <feature/manager.hpp>

std::atomic<bool> is_initialized{false};

imgui_manager::~imgui_manager() noexcept {
    if (is_initialized.exchange(false)) {
        shutdown_imgui();
    }
}

void imgui_manager::configure_style() noexcept {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
}

void imgui_manager::load_fonts() const noexcept {
    auto* fonts = ImGui::GetIO().Fonts;
    ImFontConfig cfg{};
    auto* cyrillic = fonts->GetGlyphRangesCyrillic();

    fonts->AddFontFromMemoryTTF( GloryMedium, sizeof( GloryMedium ), 16.f, &cfg, cyrillic );
    g_imgui_data.glory_bold = fonts->AddFontFromMemoryTTF( GloryExtraBold, sizeof( GloryExtraBold ), 16.f, &cfg, cyrillic );
    g_imgui_data.main_icon = fonts->AddFontFromMemoryTTF( Icons, sizeof( Icons ), 16.f, &cfg, cyrillic );
}

void imgui_manager::configure_imgui() noexcept {
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();
    configure_style();
}
void imgui_manager::initialize_imgui( window_handle handle, render::directx11* directx ) noexcept {
    if (is_initialized.exchange(true)) {
        return;
    }

    ImGui::CreateContext();
    configure_imgui();
    load_fonts();

    ImGui_ImplWin32_Init( handle );
    ImGui_ImplDX11_Init( directx->get_device(), directx->get_context() );
}

void imgui_manager::render_main_window( menu_settings settings ) noexcept {
    ImGui::SetNextWindowSize( ImVec2( settings.width, settings.height ), ImGuiCond_Once );
    ImGui::Begin( random_string::get_stable().c_str(), nullptr, settings.window_flags );
    {
        if ( ImGui::BeginTabBar( random_string::get_stable().c_str() ) )
            feature::c_manager::instance().on_menu();
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void imgui_manager::render_other_window() noexcept {
    feature::c_manager::instance().on_draw();
}

void imgui_manager::render_frame( menu_settings settings, render::directx11* directx ) noexcept {
    if (!is_initialized.load()) {
        return;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    render_main_window( settings );

    render_other_window();

    directx->cleanup_outrender();
}

void imgui_manager::shutdown_imgui() noexcept {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}