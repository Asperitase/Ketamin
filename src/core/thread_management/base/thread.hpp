#pragma once

#include <functional>
#include <stop_token>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>

#include <core/thread_management/thread_config.hpp>
#include <core/thread_management/thread_stats.hpp>

namespace thread {

    class thread_handle {
    public:
        using thread_func_t = std::function<void( std::stop_token )>;

        /**
         * @brief Creates a thread handle with the given ID and configuration
         * @param id Unique identifier for the thread
         * @param config Configuration for the thread
         */
        explicit thread_handle( thread_config config = {} ) noexcept;

        /**
         * @brief Creates and starts a thread with the given function
         * @param id Unique identifier for the thread
         * @param func Function to execute in the thread
         * @param config Configuration for the thread
         * @return A new thread handle
         * @throws thread_creation_exception if thread creation fails
         */
        static std::unique_ptr<thread_handle> create( thread_func_t func, thread_config config = {} );

        ~thread_handle() noexcept;

        thread_handle( const thread_handle& ) = delete;
        thread_handle& operator=( const thread_handle& ) = delete;

        thread_handle( thread_handle&& ) noexcept = default;
        thread_handle& operator=( thread_handle&& ) noexcept = default;

        /**
         * @brief Starts the thread with the given function
         * @param func Function to execute in the thread
         * @throws thread_creation_exception if thread creation fails
         */
        void start( thread_func_t func ) noexcept;

        /**
         * @brief Requests the thread to stop
         * @return True if stop was requested, false if thread is not running
         */
        bool request_stop() noexcept;

        /**
         * @brief Requests the thread to stop and waits for it to complete
         * @param timeout Optional timeout for waiting
         * @return True if the thread stopped, false if timeout occurred
         */
        bool stop( std::chrono::milliseconds timeout = std::chrono::milliseconds{ 0 } ) noexcept;

        /**
         * @brief Detaches the thread, allowing it to run independently
         * @return True if the thread was detached, false if not running
         */
        bool detach() noexcept;

        /**
         * @brief Waits for the thread to complete
         * @param timeout Optional timeout for waiting
         * @return True if the thread completed, false if timeout occurred
         */
        bool join( std::chrono::milliseconds timeout = std::chrono::milliseconds{ 0 } ) noexcept;

        /**
         * @brief Checks if the thread is joinable
         * @return True if the thread is joinable
         */
        [[nodiscard]] bool joinable() const noexcept;

        /**
         * @brief Sets the thread priority
         * @param priority New priority level
         * @return True if priority was set successfully
         */
        bool set_priority( thread_priority priority ) noexcept;

        // Getters
        [[nodiscard]] const thread_config& get_config() const noexcept;
        [[nodiscard]] const thread_stats& get_stats() const noexcept;
        [[nodiscard]] thread_state get_state() const noexcept;
        [[nodiscard]] bool is_running() const noexcept;

    private:
        /**
         * @brief Updates the thread's native priority based on current config
         * @return True if priority was set successfully
         */
        bool update_native_priority() noexcept;

        /**
         * @brief Wrapper function for the thread execution
         * @param func User-provided function to execute
         * @param stop_token Stop token for cancellation
         */
        void thread_wrapper( thread_func_t func, std::stop_token stop_token ) noexcept;

    private:
        thread_config m_config;
        thread_stats m_stats;
        std::unique_ptr<std::jthread> m_thread;
        mutable std::mutex m_mutex;
    };
} // namespace thread