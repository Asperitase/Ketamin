#include "thread_stats.hpp"

namespace thread {
    thread_stats::thread_stats() noexcept: m_state( thread_state::created ), m_start_time{}, m_stop_time{}, m_iteration_count( 0 ), m_last_error{} { }

    thread_stats::thread_stats( const thread_stats& other ) noexcept
        : m_state( other.m_state.load( std::memory_order_relaxed ) ), m_start_time( other.m_start_time ), m_stop_time( other.m_stop_time ),
          m_iteration_count( other.m_iteration_count.load( std::memory_order_relaxed ) ), m_last_error( other.m_last_error ) { }

    void thread_stats::update_state( thread_state new_state ) noexcept {
        m_state.store( new_state, std::memory_order_relaxed );
    }

    void thread_stats::record_start() noexcept {
        m_start_time = std::chrono::system_clock::now();
        update_state( thread_state::running );
    }

    void thread_stats::record_stop() noexcept {
        m_stop_time = std::chrono::system_clock::now();

        // Only update state if it was running or stopping
        thread_state expected = thread_state::running;
        if ( !m_state.compare_exchange_strong( expected, thread_state::stopped ) ) {
            expected = thread_state::stopping;
            m_state.compare_exchange_strong( expected, thread_state::stopped );
        }
    }

    void thread_stats::record_iteration() noexcept {
        m_iteration_count.fetch_add( 1, std::memory_order_relaxed );
    }

    void thread_stats::record_error( std::string_view error_message ) noexcept {
        m_last_error = std::move( error_message );
        update_state( thread_state::failed );
    }

    // Getters
    thread_state thread_stats::get_state() const noexcept {
        return m_state.load( std::memory_order_relaxed );
    }

    std::chrono::system_clock::time_point thread_stats::get_start_time() const noexcept {
        return m_start_time;
    }

    std::chrono::system_clock::time_point thread_stats::get_stop_time() const noexcept {
        return m_stop_time;
    }

    std::uint64_t thread_stats::get_iteration_count() const noexcept {
        return m_iteration_count.load( std::memory_order_relaxed );
    }

    const std::optional<std::string_view>& thread_stats::get_last_error() const noexcept {
        return m_last_error;
    }

    std::chrono::milliseconds thread_stats::get_running_duration() const noexcept {
        if ( m_start_time == std::chrono::system_clock::time_point{} ) {
            return std::chrono::milliseconds{ 0 };
        }

        auto end_time = ( get_state() == thread_state::running ) ? std::chrono::system_clock::now() : m_stop_time;

        return std::chrono::duration_cast<std::chrono::milliseconds>( end_time - m_start_time );
    }

    bool thread_stats::is_running() const noexcept {
        return get_state() == thread_state::running;
    }

} // namespace thread