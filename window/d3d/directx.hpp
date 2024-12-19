#ifndef DIRECTX_HPP
#define DIRECTX_HPP

#include <d3d11.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>

#include <d3dx11.h>
#include <ImGui/imgui_impl_win32.h>

#include <memory>
#include <syscall.hpp>

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
    class c_directx final {
        using result_t = LRESULT;
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
        explicit c_directx() noexcept;
        c_directx( const c_directx& ) = delete;
        c_directx& operator=( const c_directx& ) = delete;
        c_directx( c_directx&& ) = delete;
        c_directx& operator=( c_directx&& ) = delete;
        ~c_directx() noexcept;

        [[nodiscard]] static std::unique_ptr<c_directx> create() noexcept;

        [[nodiscard]] static c_directx& instance() noexcept;

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

    private:
        static c_directx* instance_;
    };

} // namespace render

#endif // DIRECTX_HPP
