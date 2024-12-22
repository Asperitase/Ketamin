#include "imgui_manager.hpp"

#include <font/Glory.hpp>
#include <font/GloryBold.hpp>
#include <icon/icons.hpp>

#include "imgui_data.hpp"

namespace render {
    c_imgui_manager::~c_imgui_manager() noexcept {
        if ( initialize.test_and_set( std::memory_order_acquire ) )
            shutdown_imgui();
    }

    void c_imgui_manager::configure_style() noexcept {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 10.0f;
    }

    void c_imgui_manager::load_fonts() const noexcept {
        ImFontConfig font_cfg;
        imgui::data::g_imgui_data.io->Fonts->AddFontFromMemoryTTF( GloryMedium, sizeof( GloryMedium ), 16.f, &font_cfg,
                                                                   imgui::data::g_imgui_data.io->Fonts->GetGlyphRangesCyrillic() );

        imgui::data::g_imgui_data.glory_bold = imgui::data::g_imgui_data.io->Fonts->AddFontFromMemoryTTF(
            GloryExtraBold, sizeof( GloryExtraBold ), 16.f, &font_cfg, imgui::data::g_imgui_data.io->Fonts->GetGlyphRangesCyrillic() );

        imgui::data::g_imgui_data.main_icon = imgui::data::g_imgui_data.io->Fonts->AddFontFromMemoryTTF(
            Icons, sizeof( Icons ), 16.f, &font_cfg, imgui::data::g_imgui_data.io->Fonts->GetGlyphRangesCyrillic() );
    }

    void c_imgui_manager::initialize_imgui( window_handle handle, c_directx* directx ) noexcept {
        if ( initialize.test_and_set( std::memory_order_acquire ) )
            return;

        ImGui::CreateContext();
        imgui::data::g_imgui_data.io = &ImGui::GetIO();

        imgui::data::g_imgui_data.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        imgui::data::g_imgui_data.io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        imgui::data::g_imgui_data.io->IniFilename = nullptr;

        ImGui::StyleColorsDark();

        configure_style();
        load_fonts();

        ImGui_ImplWin32_Init( handle );
        ImGui_ImplDX11_Init( directx->get_device(), directx->get_context() );

        initialize.clear( std::memory_order_release );
    }

    void c_imgui_manager::render_imgui_frame( c_directx* directx ) noexcept {
        if ( !initialize.test_and_set( std::memory_order_acquire ) )
            return;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        { render(); }
        directx->cleanup_outrender();
    }

    void c_imgui_manager::shutdown_imgui() noexcept {
        if ( !initialize.test_and_set( std::memory_order_acquire ) )
            return;

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        initialize.test_and_set( std::memory_order_release );
    }
} // namespace render