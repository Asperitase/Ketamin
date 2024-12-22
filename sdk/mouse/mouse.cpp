#include "mouse.hpp"

#include <syscall.hpp>

#pragma comment( lib, "ntdll.lib" )

#include "mouse_constants.hpp"

namespace {
    // Helper function to call IOCTL control for the mouse
    bool call_move( sdk::mouse::input_t handle, sdk::mouse::mouse_input& input ) {
        IO_STATUS_BLOCK block;
        return NtDeviceIoControlFile( handle, nullptr, nullptr, nullptr, &block, sdk::mouse::offset::move, &input, sizeof( sdk::mouse::mouse_input ),
                                      nullptr, 0 ) == 0L;
    }
} // namespace

namespace sdk::mouse {
    status_block c_mouse::status_io;
    std::optional<input_t> c_mouse::input;

    c_mouse::~c_mouse() noexcept {
        cleanup();
    }

    [[nodiscard]] c_mouse& c_mouse::instance() noexcept {
        static c_mouse instance;
        return instance;
    }

    bool c_mouse::startup() noexcept {
        for ( const auto& device_name : device_names ) {
            UNICODE_STRING name;
            OBJECT_ATTRIBUTES attr;
            RtlInitUnicodeString( &name, device_name );
            InitializeObjectAttributes( &attr, &name, 0, nullptr, nullptr );

            NTSTATUS status = NtCreateFile( &input.emplace(), GENERIC_WRITE | SYNCHRONIZE, &attr, &status_io, 0, FILE_ATTRIBUTE_NORMAL, 0, 3,
                                            FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, 0, 0 );

            if ( NT_SUCCESS( status ) )
                return true;
        }
        return false;
    }

    void c_mouse::cleanup() noexcept {
        if ( input ) {
            shadowsyscall( "ZwClose", input.value() );
            input.reset();
        }
    }

    void c_mouse::move( mouse_event_t event, char x, char y, char wheel, char unk_ ) noexcept {
        mouse_input i_buffer( event, x, y, wheel, unk_ );

        call_move( input.value(), i_buffer );
    }
} // namespace sdk::mouse