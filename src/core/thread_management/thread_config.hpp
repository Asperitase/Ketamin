#pragma once

#include "thread_types.hpp"

namespace thread {
    class thread_config {
    public:
        /**
         * @brief Constructor with default values
         * @param name Thread name for identification and debugging
         * @param priority Thread scheduling priority
         * @param stack_size Size of thread stack in bytes (0 = default)
         */
        thread_config( std::string name = "unnamed_thread", thread_priority priority = thread_priority::normal, std::size_t stack_size = 0 ) noexcept
            : m_name( std::move( name ) ), m_priority( priority ), m_stack_size( stack_size ) { }

        // Getters
        [[nodiscard]] const std::string& get_name() const noexcept {
            return m_name;
        }
        [[nodiscard]] thread_priority get_priority() const noexcept {
            return m_priority;
        }
        [[nodiscard]] std::size_t get_stack_size() const noexcept {
            return m_stack_size;
        }

        // Setters
        void set_name( std::string name ) noexcept {
            m_name = std::move( name );
        }
        void set_priority( thread_priority priority ) noexcept {
            m_priority = priority;
        }
        void set_stack_size( std::size_t stack_size ) noexcept {
            m_stack_size = stack_size;
        }

    private:
        std::string m_name;
        thread_priority m_priority;
        std::size_t m_stack_size;
    };

} // namespace thread