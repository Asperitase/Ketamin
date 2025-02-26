#pragma once

#include "thread.hpp"

#include <core/thread_management/registry/thread_registry.hpp>

namespace thread {
    class thread_manager {
        using thread_id_t = std::string;
        using thread_func_t = std::function<void( std::stop_token )>;

    public:
        /**
         * @brief Gets the singleton instance
         * @return Reference to the thread manager instance
         */
        static thread_manager& instance() noexcept;

        /**
         * @brief Creates and starts a thread with the given function
         * @param id Unique identifier for the thread
         * @param func Function to execute in the thread
         * @param config Configuration for the thread
         * @return Shared pointer to the thread handle
         * @throws thread_creation_exception if thread creation fails
         * @throws thread_exception if a thread with this ID already exists
         */
        std::shared_ptr<thread_handle> create_thread( thread_func_t func, thread_config config )noexcept;

        /**
         * @brief Creates and starts a thread with a regular loop function
         *
         * This version is for creating threads that run a function repeatedly
         * until stopped.
         *
         * @param id Unique identifier for the thread
         * @param loop_func Function to execute in a loop
         * @param interval Interval between loop iterations
         * @param config Configuration for the thread
         * @return Shared pointer to the thread handle
         */
        std::shared_ptr<thread_handle> create_loop_thread( std::function<void()> loop_func,
                                                           std::chrono::milliseconds interval = std::chrono::milliseconds{ 0 },
                                                           thread_config config = {} ) noexcept;

        /**
         * @brief Stops and removes a thread by ID
         * @param id The ID of the thread to remove
         * @param timeout Timeout for the thread's join operation
         * @return true if thread was stopped and removed, false otherwise
         */
        bool remove_thread( const thread_id_t& id, std::chrono::milliseconds timeout = std::chrono::milliseconds{ 0 } ) noexcept;

        /**
         * @brief Gets a thread handle by ID
         * @param id The ID of the thread to retrieve
         * @return shared_ptr to the thread handle, or nullptr if not found
         */
        std::shared_ptr<thread_handle> get_thread( const thread_id_t& id ) noexcept;

        /**
         * @brief Gets all managed thread handles
         * @return Vector of thread handles
         */
        std::vector<std::shared_ptr<thread_handle>> get_all_threads() const noexcept;

        /**
         * @brief Gets all running thread handles
         * @return Vector of running thread handles
         */
        std::vector<std::shared_ptr<thread_handle>> get_running_threads() const noexcept;

        /**
         * @brief Checks if a thread with the given ID exists
         * @param id The ID to check
         * @return true if the thread exists, false otherwise
         */
        bool has_thread( const thread_id_t& id ) const noexcept;

        /**
         * @brief Stops all threads
         * @param timeout Timeout for each thread's join operation
         * @return Number of threads successfully stopped
         */
        std::size_t stop_all_threads( std::chrono::milliseconds timeout = std::chrono::milliseconds{ 0 } ) noexcept;

        /**
         * @brief Gets the number of managed threads
         * @return Count of managed threads
         */
        [[nodiscard]] std::size_t get_thread_count() const noexcept;
        /**
         * @brief Gets the number of running threads
         * @return Count of running threads
         */
        [[nodiscard]] std::size_t get_running_thread_count() const noexcept;
        /**
         * @brief Generate a unique thread ID
         * @param prefix Optional prefix for the ID
         * @return A unique thread ID
         */
        [[nodiscard]] static thread_id_t generate_thread_id( const std::string& prefix = "thread" ) noexcept;

    private:
        thread_manager() noexcept = default;

        ~thread_manager() noexcept;

        thread_manager( const thread_manager& ) = delete;
        thread_manager& operator=( const thread_manager& ) = delete;

    private:
        detail::thread_registry& m_registry = detail::thread_registry::instance();
        static std::atomic<std::uint64_t> s_next_id;
    };

    inline std::atomic<std::uint64_t> thread_manager::s_next_id{ 1 };
} // namespace thread