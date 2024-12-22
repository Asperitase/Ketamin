#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <optional>
#include <Windows.h>
#include <winternl.h>

#include "mouse_params.hpp"

namespace sdk::mouse {
    using input_t = HANDLE;
    using status_block = IO_STATUS_BLOCK;

    class c_mouse final {
    public:
        explicit c_mouse() noexcept = default;
        ~c_mouse() noexcept;
        c_mouse( const c_mouse& ) noexcept = delete;
        c_mouse& operator=( const c_mouse& ) noexcept = delete;
        c_mouse( c_mouse&& ) noexcept = delete;
        c_mouse& operator=( c_mouse&& ) noexcept = delete;

        [[nodiscard]] static c_mouse& instance() noexcept;

        void move( mouse_event_t event, char x, char y, char wheel, char unk_ = 0 ) noexcept;

        bool startup() noexcept;
        void cleanup() noexcept;

    private:
        static std::optional<input_t> input;
        static status_block status_io;
    };
} // namespace sdk::mouse

#endif // !MOUSE_HPP
