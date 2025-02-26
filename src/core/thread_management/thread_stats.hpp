#pragma once

#include <atomic>
#include <chrono>
#include <optional>

#include "thread_types.hpp"

namespace thread {
    class thread_stats {
    public:
        thread_stats() noexcept;

        thread_stats( const thread_stats& other ) noexcept;

        thread_stats& operator=( const thread_stats& other ) noexcept {
            if ( this != &other ) {
                m_state.store( other.m_state.load( std::memory_order_relaxed ) );
                m_start_time = other.m_start_time;
                m_stop_time = other.m_stop_time;
                m_iteration_count.store( other.m_iteration_count.load( std::memory_order_relaxed ) );
                m_last_error = other.m_last_error;
            }
            return *this;
        }

        /**
         * @brief Updates the thread state
         * @param new_state The new state of the thread
         */
        void update_state( thread_state new_state ) noexcept;

        /**
         * @brief Records that the thread has started
         */
        void record_start() noexcept;

        /**
         * @brief Records that the thread has stopped
         */
        void record_stop() noexcept;

        /**
         * @brief Records an iteration of the thread's main loop
         */
        void record_iteration() noexcept;

        /**
         * @brief Records an error in the thread
         * @param error_message Description of the error
         */
        void record_error( std::string_view error_message ) noexcept;

        // Getters
        [[nodiscard]] thread_state get_state() const noexcept;

        [[nodiscard]] std::chrono::system_clock::time_point get_start_time() const noexcept;

        [[nodiscard]] std::chrono::system_clock::time_point get_stop_time() const noexcept;

        [[nodiscard]] std::uint64_t get_iteration_count() const noexcept;

        [[nodiscard]] const std::optional<std::string_view>& get_last_error() const noexcept;

        /**
         * @brief Calculates the thread's running duration
         * @return Duration the thread has been running, or has run for if stopped
         */
        [[nodiscard]] std::chrono::milliseconds get_running_duration() const noexcept;

        [[nodiscard]] bool is_running() const noexcept;

    private:
        std::atomic<thread_state> m_state;
        std::chrono::system_clock::time_point m_start_time;
        std::chrono::system_clock::time_point m_stop_time;
        std::atomic<std::uint64_t> m_iteration_count;
        std::optional<std::string_view> m_last_error;
    };
} // namespace thread