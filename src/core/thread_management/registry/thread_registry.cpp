#include "thread_registry.hpp"

#include <algorithm>

namespace thread::detail {

    thread_registry& thread_registry::instance() noexcept {
        static thread_registry registry;
        return registry;
    }

    bool thread_registry::register_thread( std::shared_ptr<thread_handle> handle ) noexcept {
        if ( !handle ) {
            return false;
        }

        std::unique_lock lock( m_mutex );
        const auto& id = handle->get_config().get_name();

        if ( m_threads.contains( id ) ) {
            return false;
        }

        m_threads.emplace( id, std::move( handle ) );
        return true;
    }

    bool thread_registry::unregister_thread( const thread_id_t& id ) noexcept {
        std::unique_lock lock( m_mutex );
        return m_threads.erase( id ) > 0;
    }

    std::shared_ptr<thread_handle> thread_registry::get_thread( const thread_id_t& id ) noexcept {
        std::shared_lock lock( m_mutex );
        auto it = m_threads.find( id );

        if ( it != m_threads.end() ) {
            return it->second;
        }

        return nullptr;
    }

    bool thread_registry::has_thread( const thread_id_t& id ) const noexcept {
        std::shared_lock lock( m_mutex );
        return m_threads.contains( id );
    }

    std::vector<std::shared_ptr<thread_handle>> thread_registry::get_all_threads() const noexcept {
        std::shared_lock lock( m_mutex );
        std::vector<std::shared_ptr<thread_handle>> result;
        result.reserve( m_threads.size() );

        for ( const auto& [id, handle] : m_threads ) {
            result.push_back( handle );
        }

        return result;
    }

    std::vector<std::shared_ptr<thread_handle>> thread_registry::get_running_threads() const noexcept {
        std::shared_lock lock( m_mutex );
        std::vector<std::shared_ptr<thread_handle>> result;

        for ( const auto& [id, handle] : m_threads ) {
            if ( handle && handle->is_running() ) {
                result.push_back( handle );
            }
        }

        return result;
    }

    std::size_t thread_registry::stop_all_threads( std::chrono::milliseconds timeout ) noexcept {
        auto threads = get_all_threads();
        std::size_t stopped_count = 0;

        for ( auto& handle : threads ) {
            if ( handle && handle->stop( timeout ) ) {
                stopped_count++;
            }
        }

        return stopped_count;
    }

    void thread_registry::for_each_thread( std::function<void( const std::shared_ptr<thread_handle>& )> func ) const noexcept {
        if ( !func ) {
            return;
        }

        auto threads = get_all_threads();

        for ( const auto& handle : threads ) {
            if ( handle ) {
                func( handle );
            }
        }
    }

    // Getters
    std::size_t thread_registry::get_thread_count() const noexcept {
        std::shared_lock lock( m_mutex );
        return m_threads.size();
    }

    std::size_t thread_registry::get_running_thread_count() const noexcept {
        std::shared_lock lock( m_mutex );
        return std::count_if( m_threads.begin(), m_threads.end(), []( const auto& pair ) {
            return pair.second && pair.second->is_running();
        } );
    }
} // namespace thread::detail