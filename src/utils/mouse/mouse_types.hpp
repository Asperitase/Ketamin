#pragma once

#include <array>
#include <concepts>
#include <Windows.h>

namespace mouse {
    class mouse_handle {
    public:
        explicit mouse_handle( HANDLE handle = nullptr ) noexcept: handle_( handle ) { }
        ~mouse_handle() noexcept {
            if ( handle_ )
                CloseHandle( handle_ );
        }

        mouse_handle( const mouse_handle& ) = delete;
        mouse_handle& operator=( const mouse_handle& ) = delete;

        mouse_handle( mouse_handle&& other ) noexcept: handle_( other.handle_ ) {
            other.handle_ = nullptr;
        }

        mouse_handle& operator=( mouse_handle&& other ) noexcept {
            if ( this != &other ) {
                if ( handle_ )
                    CloseHandle( handle_ );
                handle_ = other.handle_;
                other.handle_ = nullptr;
            }
            return *this;
        }

        [[nodiscard]] HANDLE get() const noexcept {
            return handle_;
        }
        explicit operator bool() const noexcept {
            return handle_ != nullptr;
        }

    private:
        HANDLE handle_;
    };

    enum class mouse_event : char {
        none = 0,
        press = 1,
        release = 2,
        move = 3,
        click = 4
    };

    struct mouse_input {
        mouse_event event;
        char x;
        char y;
        char wheel;
        char reserved;
    };
} // namespace mouse
