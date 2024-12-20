#include "window.hpp"

#include <cassert>
#include <syscall.hpp>

namespace render {
    c_window::c_window() noexcept {
        window_class_t = { sizeof( window_class_t ),
                           CS_CLASSDC,
                           window_proccess,
                           0L,
                           0L,
                           shadowcall<HMODULE>( "GetModuleHandleA", nullptr ),
                           nullptr,
                           nullptr,
                           nullptr,
                           nullptr,
                           WINDOW_CLASS_NAME,
                           nullptr };

        if ( !::shadowcall<atom>( "RegisterClassExA", &window_class_t ) )
            return;
    }

    void c_window::reset() noexcept {
        shutdown_imgui();

        if ( handle ) {
            ::shadowcall<BOOL>( "DestroyWindow", handle.value() );
            handle.reset();
        }

        ::shadowcall<BOOL>( "UnregisterClassA", window_class_t.lpszClassName, window_class_t.hInstance );
    }

    c_window::~c_window() noexcept {
        reset();
    }

    [[nodiscard]] std::unique_ptr<c_window> c_window::create() noexcept {
        return std::make_unique<c_window>();
    }

    void c_window::create_window_handle() noexcept {
        handle = ::shadowcall<HWND>( "CreateWindowExA", 0L, window_class_t.lpszClassName, WINDOW_NAME, WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                     window_class_t.hInstance, nullptr );

        if ( !handle )
            return;

        ::shadowcall<BOOL>( "ShowWindow", handle.value(), SW_HIDE );
        ::shadowcall<BOOL>( "UpdateWindow", handle.value() );
    }

    void c_window::render_loop() noexcept {
        const auto directx = c_directx::create();
        if ( !directx->create_device( handle.value() ) ) {
            directx->cleanup_device();
            reset();
            return;
        }

        initialize_imgui( handle.value(), directx.get() );

        bool done = false;
        while ( !done ) {
            MSG msg;
            while ( ::shadowcall<BOOL>( "PeekMessageA", &msg, nullptr, 0U, 0U, PM_REMOVE ) ) {
                ::shadowcall<BOOL>( "TranslateMessage", &msg );
                ::shadowcall<LRESULT>( "DispatchMessageA", &msg );
                if ( msg.message == WM_QUIT )
                    done = true;
            }
            if ( done )
                break;

            render_imgui_frame( directx.get() );
        }

        directx->cleanup_device();
        reset();
    }
} // namespace render