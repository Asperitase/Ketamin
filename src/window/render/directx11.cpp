#include "directx11.hpp"

namespace render {
    directx11::directx11() noexcept {
        shadowcall( "LoadLibraryA", "d3d11.dll" );
    }

    directx11::~directx11() {
        cleanup_device();
    }

    [[nodiscard]] std::unique_ptr<directx11> directx11::create() noexcept {
        return std::make_unique<directx11>();
    }

    bool directx11::create_device( handle window ) noexcept {
        if ( device ) {
            assert( device && "Device already created. Skipping reinitialization." );
            return false;
        }

        DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
        ZeroMemory( &swap_chain_desc, sizeof( swap_chain_desc ) );
        swap_chain_desc.BufferCount = 2;
        swap_chain_desc.BufferDesc.Width = 0;
        swap_chain_desc.BufferDesc.Height = 0;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = window;
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = TRUE;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT device_flags = 0;
        D3D_FEATURE_LEVEL feature_level;
        const D3D_FEATURE_LEVEL feature_level_array[2] = {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_0,
        };

        IDXGISwapChain* raw_swap_chain = nullptr;
        ID3D11Device* raw_device = nullptr;
        ID3D11DeviceContext* raw_context = nullptr;

        result_t res =
            shadowcall<result_t>( "D3D11CreateDeviceAndSwapChain", nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, device_flags, feature_level_array, 2,
                                  D3D11_SDK_VERSION, &swap_chain_desc, &raw_swap_chain, &raw_device, &feature_level, &raw_context );

        if ( res == DXGI_ERROR_UNSUPPORTED ) {
            res = shadowcall<result_t>( "D3D11CreateDeviceAndSwapChain", nullptr, D3D_DRIVER_TYPE_WARP, nullptr, device_flags, feature_level_array, 2,
                                        D3D11_SDK_VERSION, &swap_chain_desc, &raw_swap_chain, &raw_device, &feature_level, &raw_context );
        }

        if ( FAILED( res ) ) {
            return false;
        }

        swap_chain.reset( raw_swap_chain );
        device.reset( raw_device );
        context.reset( raw_context );

        create_target();

        return true;
    }

    void directx11::cleanup_outrender() noexcept {
        const float clear_color_with_alpha[4] = { 0, 0, 0, 0 };

        ID3D11RenderTargetView* const target_views[] = { target_view.get() };
        context->OMSetRenderTargets( 1, target_views, nullptr );
        context->ClearRenderTargetView( target_view.get(), clear_color_with_alpha );

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        swap_chain->Present( 1, 0 ); // Present with vsync
    }

    void directx11::create_target() noexcept {
        ID3D11Texture2D* back_buffer = nullptr;
        if ( SUCCEEDED( swap_chain->GetBuffer( 0, IID_PPV_ARGS( &back_buffer ) ) ) ) {
            ID3D11RenderTargetView* raw_target_view = nullptr;
            if ( SUCCEEDED( device->CreateRenderTargetView( back_buffer, nullptr, &raw_target_view ) ) ) {
                target_view.reset( raw_target_view );
            }
            back_buffer->Release();
        }
    }

    void directx11::cleanup_device() noexcept {
        target_view.reset();
        swap_chain.reset();
        context.reset();
        device.reset();
    }

    [[nodiscard]] ID3D11Device* directx11::get_device() const noexcept {
        return device.get();
    }

    [[nodiscard]] ID3D11DeviceContext* directx11::get_context() const noexcept {
        return context.get();
    }

    [[nodiscard]] IDXGISwapChain* directx11::get_swapchain() const noexcept {
        return swap_chain.get();
    }

    [[nodiscard]] ID3D11RenderTargetView* directx11::get_targetview() const noexcept {
        return target_view.get();
    }

} // namespace render