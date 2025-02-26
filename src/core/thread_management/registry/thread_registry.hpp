#pragma once

#include <shared_mutex>
#include <unordered_map>

#include <core/thread_management/base/thread.hpp>

namespace thread::detail {
    /**
     * @brief Registry for managing thread handles
     *
     * This class maintains a global registry of all thread handles,
     * providing thread-safe access to them.
     */
    class thread_registry {
    public:
        using thread_id_t = std::string;
        using thread_map_t = std::unordered_map<thread_id_t, std::shared_ptr<thread_handle>>;

        /**
         * @brief Get the singleton instance
         * @return Reference to the thread registry instance
         */
        static thread_registry& instance() noexcept;

        /**
         * @brief Registers a thread handle
         * @param handle The thread handle to register
         * @return true if registration succeeded, false if ID already exists
         */
        bool register_thread( std::shared_ptr<thread_handle> handle ) noexcept;

        /**
         * @brief Unregisters a thread by ID
         * @param id The ID of the thread to unregister
         * @return true if unregistered, false if not found
         */
        bool unregister_thread( const thread_id_t& id ) noexcept;

        /**
         * @brief Gets a thread handle by ID
         * @param id The ID of the thread to retrieve
         * @return shared_ptr to the thread handle, or nullptr if not found
         */
        std::shared_ptr<thread_handle> get_thread( const thread_id_t& id ) noexcept;

        /**
         * @brief Checks if a thread with the given ID exists
         * @param id The ID to check
         * @return true if the thread exists, false otherwise
         */
        bool has_thread( const thread_id_t& id ) const noexcept;

        /**
         * @brief Gets all registered thread handles
         * @return A vector of all thread handles
         */
        std::vector<std::shared_ptr<thread_handle>> get_all_threads() const noexcept;

        /**
         * @brief Gets all running thread handles
         * @return A vector of running thread handles
         */
        std::vector<std::shared_ptr<thread_handle>> get_running_threads() const noexcept;
        /**
         * @brief Stops all threads
         * @param timeout Timeout for each thread's join operation
         * @return Number of threads successfully stopped
         */
        std::size_t stop_all_threads( std::chrono::milliseconds timeout = std::chrono::milliseconds{ 0 } ) noexcept;

        /**
         * @brief Applies a function to each thread
         * @param func Function to apply to each thread
         */
        void for_each_thread( std::function<void( const std::shared_ptr<thread_handle>& )> func ) const noexcept;

        /**
         * @brief Gets the number of registered threads
         * @return Count of registered threads
         */
        [[nodiscard]] std::size_t get_thread_count() const noexcept;

        /**
         * @brief Gets the number of running threads
         * @return Count of running threads
         */
        [[nodiscard]] std::size_t get_running_thread_count() const noexcept;

    private:
        thread_registry() noexcept = default;
        ~thread_registry() noexcept = default;
        thread_registry( const thread_registry& ) = delete;
        thread_registry& operator=( const thread_registry& ) = delete;

    private:
        mutable std::shared_mutex m_mutex;
        thread_map_t m_threads;
    };
} // namespace thread::detail