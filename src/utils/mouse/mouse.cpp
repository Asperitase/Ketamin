#include "mouse.hpp"
#include <array>
#include <winternl.h>

namespace {
    constexpr std::array<const wchar_t*, 2> device_paths = { L"\\??\\ROOT#SYSTEM#0002#{1abc05c0-c378-41b9-9cef-df1aba82b015}",
                                                             L"\\??\\ROOT#SYSTEM#0001#{1abc05c0-c378-41b9-9cef-df1aba82b015}" };
    constexpr ULONG MOUSE_MOVE_IOCTL = 0x2a2010;

    [[nodiscard]] UNICODE_STRING create_unicode_string( const wchar_t* str ) noexcept {
        UNICODE_STRING result;
        RtlInitUnicodeString( &result, str );
        return result;
    }
} // namespace

namespace mouse {

    class mouse::impl {
    public:
        impl() noexcept = default;
        ~impl() noexcept = default;

        [[nodiscard]] result<bool> initialize() noexcept {
            if ( handle_ ) {
                return true;
            }

            for ( const auto* device_path : device_paths ) {
                auto result = try_open_device( device_path );
                if ( result.is_success() && result.value() ) {
                    return true;
                }
            }

            return result<bool>{ result<bool>::error_t{ STATUS_DEVICE_NOT_CONNECTED, "Failed to open any mouse device" } };
        }

        void shutdown() noexcept {
            handle_ = mouse_handle{};
        }

        [[nodiscard]] result<bool> move( mouse_input input ) noexcept {
            if ( !handle_ ) {
                return result<bool>{ result<bool>::error_t{ STATUS_DEVICE_NOT_CONNECTED, "Device not initialized" } };
            }

            IO_STATUS_BLOCK io_status{};
            NTSTATUS status =
                NtDeviceIoControlFile( handle_.get(), nullptr, nullptr, nullptr, &io_status, MOUSE_MOVE_IOCTL, &input, sizeof( mouse_input ), nullptr, 0 );

            if ( !NT_SUCCESS( status ) ) {
                return result<bool>{ result<bool>::error_t{ status, "Failed to send mouse input" } };
            }

            return true;
        }

        [[nodiscard]] bool is_initialized() const noexcept {
            return static_cast<bool>( handle_ );
        }

    private:
        [[nodiscard]] result<bool> try_open_device( const wchar_t* device_path ) noexcept {
            UNICODE_STRING name = create_unicode_string( device_path );
            OBJECT_ATTRIBUTES attrs{};
            InitializeObjectAttributes( &attrs, &name, 0, nullptr, nullptr );

            HANDLE raw_handle{};
            IO_STATUS_BLOCK io_status{};

            NTSTATUS status = NtCreateFile( &raw_handle, GENERIC_WRITE | SYNCHRONIZE, &attrs, &io_status, nullptr, FILE_ATTRIBUTE_NORMAL, 0, FILE_OPEN,
                                            FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, nullptr, 0 );

            if ( !NT_SUCCESS( status ) ) {
                return result<bool>{ result<bool>::error_t{ status, "Failed to create file" } };
            }

            handle_ = mouse_handle{ raw_handle };
            return true;
        }

        mouse_handle handle_;
    };

    mouse::mouse() noexcept: pimpl_( std::make_unique<impl>() ) { }
    mouse::~mouse() noexcept = default;

    mouse& mouse::instance() noexcept {
        static mouse instance;
        return instance;
    }

    result<bool> mouse::initialize() noexcept {
        return pimpl_->initialize();
    }

    void mouse::shutdown() noexcept {
        pimpl_->shutdown();
    }

    result<bool> mouse::move( mouse_input input ) noexcept {
        return pimpl_->move( input );
    }

    bool mouse::is_initialized() const noexcept {
        return pimpl_->is_initialized();
    }

} // namespace mouse