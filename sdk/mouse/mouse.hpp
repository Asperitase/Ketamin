#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <array>
#include <common.hpp>
#include <optional>
#include <Windows.h>
#include <winternl.h>

namespace sdk::mouse {
    using input_t = HANDLE;
    using char_t = const wchar_t*;
    using status_block = IO_STATUS_BLOCK;

    class c_mouse final {
        static constexpr std::array<char_t, 2> device_names = { L"\\??\\ROOT#SYSTEM#0002#{1abc05c0-c378-41b9-9cef-df1aba82b015}",
                                                                L"\\??\\ROOT#SYSTEM#0001#{1abc05c0-c378-41b9-9cef-df1aba82b015}" };

    public:
        explicit c_mouse() noexcept;
        ~c_mouse() noexcept;
        c_mouse( const c_mouse& ) noexcept = delete;
        c_mouse& operator=( const c_mouse& ) noexcept = delete;
        c_mouse( c_mouse&& ) noexcept = delete;
        c_mouse& operator=( c_mouse&& ) noexcept = delete;

        [[nodiscard]] static c_mouse& instance() noexcept;

        void move( sdk::common::mouse_button button, char x, char y, char wheel, char unk_ = 0 ) noexcept;

        bool startup() noexcept;
        void cleanup() noexcept;

    private:
        static std::optional<input_t> input;
        static status_block status_io;

    private:
        static c_mouse* instance_;
    };
} // namespace sdk::mouse

#endif // !MOUSE_HPP
