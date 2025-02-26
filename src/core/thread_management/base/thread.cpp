#include "thread.hpp"

#include <utils/logger.hpp>

namespace thread {
    thread_handle::thread_handle( thread_config config ) noexcept: m_config( std::move( config ) ), m_stats(), m_thread( nullptr ) { }

    std::unique_ptr<thread_handle> thread_handle::create( thread_func_t func, thread_config config ) {
        auto handle = std::make_unique<thread_handle>( std::move( config ) );
        handle->start( std::move( func ) );
        return handle;
    }

    thread_handle::~thread_handle() noexcept {
        if ( m_thread && m_thread->joinable() ) {
            request_stop();
        }
    }

    void thread_handle::start( thread_func_t func ) noexcept {
        std::unique_lock lock( m_mutex );

        if ( m_thread && m_thread->joinable() ) {
            CONSOLE_INFO( "Thread {} is already running | stack: {}\n", m_config.get_name(), m_config.get_stack_size() );
        }

        // Reset stats for new run
        m_stats = thread_stats();

        // Create the thread with our wrapper function
        m_thread = std::make_unique<std::jthread>( [this, func = std::move( func )]( std::stop_token stop_token ) {
            thread_wrapper( func, stop_token );
        } );

        // Set thread priority
        update_native_priority();
    }

    bool thread_handle::request_stop() noexcept {
        std::unique_lock lock( m_mutex );

        if ( !m_thread || !m_thread->joinable() ) {
            return false;
        }

        m_stats.update_state( thread_state::stopping );
        m_thread->request_stop();
        return true;
    }

    bool thread_handle::stop( std::chrono::milliseconds timeout ) noexcept {
        if ( !request_stop() ) {
            return false;
        }

        return join( timeout );
    }

    bool thread_handle::detach() noexcept {
        std::unique_lock lock( m_mutex );

        if ( !m_thread || !m_thread->joinable() ) {
            return false;
        }

        m_thread->detach();
        m_stats.update_state( thread_state::detached );
        return true;
    }

    bool thread_handle::join( std::chrono::milliseconds timeout ) noexcept {
        std::unique_lock lock( m_mutex );

        if ( !m_thread || !m_thread->joinable() ) {
            return false;
        }

        if ( timeout > std::chrono::milliseconds{ 0 } ) {
            // Use a separate thread to join with timeout
            std::promise<bool> join_completed;
            auto future = join_completed.get_future();

            std::thread join_thread( [this, &join_completed]() {
                if ( m_thread ) {
                    m_thread->join();
                }
                join_completed.set_value( true );
            } );

            join_thread.detach();

            // Wait for join to complete with timeout
            if ( future.wait_for( timeout ) == std::future_status::timeout ) {
                return false;
            }

            return future.get();
        } else {
            // Join without timeout
            if ( m_thread ) {
                m_thread->join();
            }
            return true;
        }
    }

    bool thread_handle::update_native_priority() noexcept {
        if ( !m_thread ) {
            return false;
        }

        auto native_handle = m_thread->native_handle();
        int win_priority;

        switch ( m_config.get_priority() ) {
        case thread_priority::lowest:
            win_priority = THREAD_PRIORITY_IDLE;
            break;
        case thread_priority::below_normal:
            win_priority = THREAD_PRIORITY_BELOW_NORMAL;
            break;
        case thread_priority::normal:
            win_priority = THREAD_PRIORITY_NORMAL;
            break;
        case thread_priority::above_normal:
            win_priority = THREAD_PRIORITY_ABOVE_NORMAL;
            break;
        case thread_priority::highest:
            win_priority = THREAD_PRIORITY_HIGHEST;
            break;
        case thread_priority::real_time:
            win_priority = THREAD_PRIORITY_TIME_CRITICAL;
            break;
        default:
            win_priority = THREAD_PRIORITY_NORMAL;
        }

        return SetThreadPriority( native_handle, win_priority ) != 0;
    }

    void thread_handle::thread_wrapper( thread_func_t func, std::stop_token stop_token ) noexcept {
        // Record start time and update state
        m_stats.record_start();

        // Call the actual function
        func( std::move( stop_token ) );

        // Record completion
        m_stats.record_stop();
        m_stats.update_state( thread_state::completed );
    }

    bool thread_handle::joinable() const noexcept {
        std::unique_lock lock( m_mutex );
        return m_thread && m_thread->joinable();
    }

    bool thread_handle::set_priority( thread_priority priority ) noexcept {
        std::unique_lock lock( m_mutex );
        m_config.set_priority( priority );
        return update_native_priority();
    }

    // Getters
    const thread_config& thread_handle::get_config() const noexcept {
        return m_config;
    }
    const thread_stats& thread_handle::get_stats() const noexcept {
        return m_stats;
    }
    thread_state thread_handle::get_state() const noexcept {
        return m_stats.get_state();
    }
    bool thread_handle::is_running() const noexcept {
        return m_stats.is_running();
    }

} // namespace thread