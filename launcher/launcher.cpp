#include "launcher.hpp"

#include <window.hpp>

namespace global {
    [[nodiscard]] c_launcher& c_launcher::instance() noexcept {
        static c_launcher instance;
        return instance;
    }

    int c_launcher::start() const noexcept {
        shadowcall<bool>( "SetPriorityClass", ( HANDLE )-1, HIGH_PRIORITY_CLASS );

        const auto render = render::c_window::create();
        if ( !render ) {
            shadowcall<int>( "MessageBoxA", NULL, "Failed to create render window.", "render", MB_OK );
            return -1;
        }

        render->create_window_handle();
        render->render_loop();
        return 1;
    }
} // namespace global