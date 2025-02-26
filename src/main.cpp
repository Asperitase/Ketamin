#include "core/core.hpp"
#include "utils/logger.hpp"
#include <shadowsyscall.hpp>
#include <window/window.hpp>

[[nodiscard]] static std::unique_ptr<window::window> initialize_window() noexcept {
#if ( !_DEBUG )
    if ( !::shadowcall<BOOL>( "ShowWindow", GetConsoleWindow(), SW_HIDE ) ) {
        CONSOLE_ERROR( "Failed to hide console window\n" );
    }
#endif

    auto window = window::window::create();
    if ( !window ) {
        CONSOLE_ERROR( "Failed to create window\n" );
        return nullptr;
    }
    return window;
}

/**
 * @brief Main application entry point
 * @return Exit code, 0 on success, non-zero on failure
 */

int main() {
    auto window = initialize_window();
    if ( !window ) {
        return EXIT_FAILURE;
    }

    auto& launcher = core::launcher::instance();

    auto status = launcher.start( window );
    if ( status.is_success() ) [[likely]] {
        CONSOLE_INFO( "Application started successfully\n" );
        window->render_loop( launcher.get_settings() );
        return EXIT_SUCCESS;
    }

    CONSOLE_ERROR( "Application failed to start\n" );
    return launcher.shutdown( status );
}
