#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <external/ImGui/imgui.h>
#include <external/ImGui/imgui_impl_dx11.h>
#include <external/ImGui/imgui_impl_win32.h>

#include <memory>
#include <shadowsyscall.hpp>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT message, WPARAM param, LPARAM lParam );
inline LRESULT window_proccess( HWND window_handle, UINT message, WPARAM param, LPARAM lParam ) {
    if ( ImGui_ImplWin32_WndProcHandler( window_handle, message, param, lParam ) )
        return true;

    switch ( message ) {
    case WM_SYSCOMMAND:
        if ( ( param & 0xfff0 ) == SC_KEYMENU )
            return false;
        break;
    case WM_DESTROY:
        ::shadowcall<void>( "PostQuitMessage", 0x0 );
        return false;
    }

    return ::shadowcall<LRESULT>( "DefWindowProcA", window_handle, message, param, lParam );
}

namespace render {
    class directx11 final {
        using result_t = HRESULT;
        using handle = HWND;

        static inline std::unique_ptr<ID3D11Device, void ( * )( ID3D11Device* )> device{ nullptr, []( ID3D11Device* d ) {
                                                                                            if ( d )
                                                                                                d->Release();
                                                                                        } };
        static inline std::unique_ptr<ID3D11DeviceContext, void ( * )( ID3D11DeviceContext* )> context{ nullptr, []( ID3D11DeviceContext* c ) {
                                                                                                           if ( c )
                                                                                                               c->Release();
                                                                                                       } };
        static inline std::unique_ptr<IDXGISwapChain, void ( * )( IDXGISwapChain* )> swap_chain{ nullptr, []( IDXGISwapChain* s ) {
                                                                                                    if ( s )
                                                                                                        s->Release();
                                                                                                } };
        static inline std::unique_ptr<ID3D11RenderTargetView, void ( * )( ID3D11RenderTargetView* )> target_view{ nullptr,
                                                                                                                  []( ID3D11RenderTargetView* t ) {
                                                                                                                      if ( t )
                                                                                                                          t->Release();
                                                                                                                  } };

    public:
        explicit directx11() noexcept;

        directx11( const directx11& ) = delete;
        directx11& operator=( const directx11& ) = delete;
        directx11( directx11&& ) = delete;
        directx11& operator=( directx11&& ) = delete;

        ~directx11() noexcept;

        [[nodiscard]] static std::unique_ptr<directx11> create() noexcept;

    public:
        bool create_device( handle window ) noexcept;
        void create_target() noexcept;

        void cleanup_device() noexcept;
        void cleanup_outrender() noexcept;

    public:
        [[nodiscard]] ID3D11Device* get_device() const noexcept;
        [[nodiscard]] ID3D11DeviceContext* get_context() const noexcept;
        [[nodiscard]] IDXGISwapChain* get_swapchain() const noexcept;
        [[nodiscard]] ID3D11RenderTargetView* get_targetview() const noexcept;
    };

} // namespace render