#include "thread_manager.hpp"

#include <utils/logger.hpp>

namespace thread {
    thread_manager::~thread_manager() noexcept {
        // Stop all threads when the manager is destroyed
        m_registry.stop_all_threads( std::chrono::milliseconds{ 100 } );
    }

    thread_manager& thread_manager::instance() noexcept {
        static thread_manager manager;
        return manager;
    }

    std::shared_ptr<thread_handle> thread_manager::create_thread( thread_func_t func, thread_config config ) noexcept {
        if ( m_registry.has_thread( config.get_name() ) ) {
            CONSOLE_INFO( "Thread with ID {} already exists\n", config.get_name() );
        }

        auto handle = std::make_shared<thread_handle>( config );
        handle->start( std::move( func ) );

        if ( !m_registry.register_thread( handle ) ) {
            // This should not happen since we checked for existence above
            CONSOLE_INFO( "Failed to register thread with ID {}\n", config.get_name() );
        }

        return handle;
    }

    std::shared_ptr<thread_handle> thread_manager::create_loop_thread( std::function<void()> loop_func,
                                                                       std::chrono::milliseconds interval, thread_config config ) noexcept {
        return create_thread(
            [loop_func, interval]( std::stop_token stop_token ) {
                while ( !stop_token.stop_requested() ) {
                    // Call the user function
                    loop_func();

                    // Sleep if interval is specified
                    if ( interval > std::chrono::milliseconds{ 0 } ) {
                        std::this_thread::sleep_for( interval );
                    }
                }
            },
            config );
    }

    bool thread_manager::remove_thread( const thread_id_t& id, std::chrono::milliseconds timeout ) noexcept {
        auto handle = m_registry.get_thread( id );

        if ( !handle ) {
            return false;
        }

        bool stopped = handle->stop( timeout );
        m_registry.unregister_thread( id );

        return stopped;
    }

    std::shared_ptr<thread_handle> thread_manager::get_thread( const thread_id_t& id ) noexcept {
        return m_registry.get_thread( id );
    }

    std::vector<std::shared_ptr<thread_handle>> thread_manager::get_all_threads() const noexcept {
        return m_registry.get_all_threads();
    }

    std::vector<std::shared_ptr<thread_handle>> thread_manager::get_running_threads() const noexcept {
        return m_registry.get_running_threads();
    }

    bool thread_manager::has_thread( const thread_id_t& id ) const noexcept {
        return m_registry.has_thread( id );
    }

    std::size_t thread_manager::stop_all_threads( std::chrono::milliseconds timeout ) noexcept {
        return m_registry.stop_all_threads( timeout );
    }

    [[nodiscard]] std::size_t thread_manager::get_thread_count() const noexcept {
        return m_registry.get_thread_count();
    }

    [[nodiscard]] std::size_t thread_manager::get_running_thread_count() const noexcept {
        return m_registry.get_running_thread_count();
    }

    [[nodiscard]] thread_manager::thread_id_t thread_manager::generate_thread_id( const std::string& prefix ) noexcept {
        std::ostringstream oss;
        oss << prefix << "_" << std::hex << std::setw( 8 ) << std::setfill( '0' ) << s_next_id.fetch_add( 1, std::memory_order_relaxed );
        return oss.str();
    }
} // namespace thread