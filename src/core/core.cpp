#include "core.hpp"

#include <shadowsyscall.hpp>

#include <rust/weapon/factory/builder/weapon_registry.hpp>

#include <utils/logger.hpp>

namespace core {
    launcher& launcher::instance() noexcept {
        static launcher instance;
        return instance;
    }

    result<bool> launcher::initialize_syscalls() const noexcept {
        if ( auto syscall_spc = shadowcall<bool>( "SetPriorityClass", reinterpret_cast<void*>( -1 ), HIGH_PRIORITY_CLASS ); !syscall_spc.result() ) {
            CONSOLE_ERROR( "Syscall_spc error | address: {}.\n", syscall_spc.export_location().base_address().ptr() );
            return result<bool>{ result<bool>::error_t{ false, "System call failed due to specific reasons." } };
        }

        return true;
    }

    result<bool> launcher::create_window( const std::unique_ptr<window::window>& window ) const noexcept {
        if ( !window ) {
            CONSOLE_ERROR( "Window pointer is null\n" );
            return result<bool>{ result<bool>::error_t{ false, "Window pointer is null" } };
        }

        if ( !window->create_window_handle() ) {
            return result<bool>{ result<bool>::error_t{ false, "Failed to create window handle." } };
        }

        CONSOLE_INFO( "Window created successfully\n" );
        return true;
    }

    result<bool> launcher::initialize_mouse() const noexcept {
        if ( auto init_result = mouse.initialize(); !init_result.is_success() ) {
            CONSOLE_ERROR( "Failed to initialize mouse: {}\n", init_result.error().message );
            return result<bool>{ result<bool>::error_t{ false, "Initialization mouse failed." } };
        }

        CONSOLE_INFO( "Mouse initialized successfully\n" );
        return true;
    }

    result<bool> launcher::start( const std::unique_ptr<window::window>& window ) const noexcept {
        shadowcall( "LoadLibraryA", "user32.dll" );

        if ( !window ) {
            CONSOLE_ERROR( "Window pointer is null\n" );
            return result<bool>{ result<bool>::error_t{ false, "Window pointer is null" } };
        }

        auto syscall_result = initialize_syscalls();
        if ( !syscall_result.is_success() ) {
            CONSOLE_ERROR( "Failed to initialize syscalls\n" );
            return syscall_result;
        }

        auto window_result = create_window( window );
        if ( !window_result.is_success() ) {
            CONSOLE_ERROR( "Failed to create window\n" );
            return window_result;
        }

        auto mouse_result = initialize_mouse();
        if ( !mouse_result.is_success() ) {
            CONSOLE_ERROR( "Failed to initialize mouse\n" );
            return mouse_result;
        }

        weapon::weapon_registry::instance().initialize();

        return mouse_result;
    }

    int launcher::shutdown( result<bool> status ) noexcept {
        shadowcall<int>( "MessageBoxA", nullptr, std::format( "Error: {}", status.error().message.data() ).c_str(), "Shutdown", MB_ICONSTOP );

        if ( mouse.is_initialized() ) {
            mouse.shutdown();
            CONSOLE_ERROR( "Success shutdown mouse.\n" );
        }

        return status.error().code;
    }

    const app_settings& launcher::get_settings() const noexcept {
        return settings_;
    }
} // namespace core