#pragma once

namespace thread {
    enum class thread_priority {
        lowest,
        below_normal,
        normal,
        above_normal,
        highest,
        real_time
    };

    [[nodiscard]] constexpr std::string_view to_string( thread_priority priority ) noexcept {
        switch ( priority ) {
        case thread_priority::lowest:
            return "Lowest";
        case thread_priority::below_normal:
            return "Below Normal";
        case thread_priority::normal:
            return "Normal";
        case thread_priority::above_normal:
            return "Above Normal";
        case thread_priority::highest:
            return "Highest";
        case thread_priority::real_time:
            return "Realtime";
        default:
            return "Unknown";
        }
    }

    enum class thread_state {
        created,   // Thread is created but not started
        running,   // Thread is actively running
        stopping,  // Thread has been requested to stop
        stopped,   // Thread has stopped normally
        detached,  // Thread is detached
        completed, // Thread has completed its task
        failed     // Thread ended with an error
    };

    [[nodiscard]] constexpr std::string_view to_string( thread_state state ) noexcept {
        switch ( state ) {
        case thread_state::created:
            return "Created";
        case thread_state::running:
            return "Running";
        case thread_state::stopping:
            return "Stopping";
        case thread_state::stopped:
            return "Stopped";
        case thread_state::detached:
            return "Detached";
        case thread_state::completed:
            return "Completed";
        case thread_state::failed:
            return "Failed";
        default:
            return "Unknown";
        }
    }

} // namespace thread
