#include "window.hpp"
#include "utils/logger.hpp"

#include <core/thread_management/base/thread_manager.hpp>
#include <feature/manager.hpp>

namespace window {

    window::window() noexcept: imgui_manager() {
        initialize_window_class();
    }

    window::~window() noexcept {
        shutdown();
    }

    std::unique_ptr<window> window::create() noexcept {
        auto window_ptr = std::make_unique<window>();
        if ( !window_ptr ) {
            CONSOLE_ERROR( "Failed to create window class\n" );
            return nullptr;
        }
        return window_ptr;
    }

    void window::shutdown() noexcept {
        is_running = false;
        if ( handle ) {
            ::shadowcall<BOOL>( "DestroyWindow", *handle );
            handle = nullptr;
        }
    }

    bool window::create_window_handle() noexcept {
        if ( !register_window_class() ) {
            CONSOLE_ERROR( "Failed to register window class\n" );
            return false;
        }

        handle = ::shadowcall<HWND>( "CreateWindowExA", 0L, window_class.lpszClassName, window_constants::window_title, WS_POPUP, 0, 0, nullptr, nullptr,
                                     nullptr, nullptr, window_class.hInstance, nullptr );

        if ( !handle ) {
            CONSOLE_ERROR( "Failed to create window handle\n" );
            return false;
        }

        ::shadowcall<BOOL>( "ShowWindow", handle.value(), SW_HIDE );
        ::shadowcall<BOOL>( "UpdateWindow", handle.value() );
        return true;
    }

    void window::render_loop( const app_settings& settings ) noexcept {
        const auto render = render::directx11::create();
        if ( !render->create_device( handle.value() ) ) {
            render->cleanup_device();
            shutdown();
            return;
        }

        initialize_imgui( handle.value(), render.get() );

        auto update_thread = thread::thread_manager::instance().create_thread(
            []( std::stop_token token ) {
                while ( !token.stop_requested() ) {
                    feature::c_manager::instance().update();

                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }
            },
            { "update_thread" } );


        is_running = true;
        while ( is_running ) {
            process_window_messages();
            if ( is_running ) {
                render_frame( settings.menu, render.get() );
            }
        }

        render->cleanup_device();
        shutdown();
    }

    window::window_handle window::get_handle() const noexcept {
        return handle;
    }

    void window::process_window_messages() noexcept {
        MSG msg{};
        while ( ::shadowcall<BOOL>( "PeekMessageA", &msg, nullptr, 0U, 0U, PM_REMOVE ) ) {
            if ( msg.message == WM_QUIT ) {
                is_running = false;
                return;
            }
            ::shadowcall<BOOL>( "TranslateMessage", &msg );
            ::shadowcall<LRESULT>( "DispatchMessageA", &msg );
        }
    }

    bool window::initialize_window_class() noexcept {
        window_class.cbSize = sizeof( WNDCLASSEX );
        window_class.style = CS_CLASSDC;
        window_class.lpfnWndProc = window_proccess;
        window_class.cbClsExtra = 0;
        window_class.cbWndExtra = 0;
        window_class.hInstance = shadowcall<HMODULE>( "GetModuleHandleA", nullptr );
        window_class.hIcon = nullptr;
        window_class.hCursor = nullptr;
        window_class.hbrBackground = nullptr;
        window_class.lpszMenuName = nullptr;
        window_class.lpszClassName = window_constants::window_class_name;
        window_class.hIconSm = nullptr;

        return true;
    }

    bool window::register_window_class() noexcept {
        if ( !RegisterClassEx( &window_class ) ) {
            CONSOLE_ERROR( "Failed to register window class\n" );
            return false;
        }
        return true;
    }

} // namespace window
