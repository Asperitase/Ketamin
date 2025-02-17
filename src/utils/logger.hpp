#pragma once

#include <chrono>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace logger {

    class logger final {
    public:
        explicit logger( const std::string& filename = "" ) noexcept {
#if ( _DEBUG )
            if ( !filename.empty() ) {
                file = std::make_unique<fmt::ostream>( fmt::output_file( filename ) );
            }
#endif
        }

        template <typename... Args>
        void log_error( fmt::format_string<Args...> format, Args&&... args ) noexcept {
            auto timestamp = current_time();
            auto message = fmt::format( format, std::forward<Args>( args )... );

            if ( file ) {
                file->print( "[{}] ERROR: {}\n", timestamp, message );
            }
            fmt::print( fmt::fg( fmt::color::red ), "[{}] ERROR: {}", timestamp, message );
        }

        template <typename... Args>
        void log_info( fmt::format_string<Args...> format, Args&&... args ) noexcept {
            auto timestamp = current_time();
            auto message = fmt::format( format, std::forward<Args>( args )... );

            if ( file ) {
                file->print( "[{}] INFO: {}\n", timestamp, message );
            }
            fmt::print( fmt::fg( fmt::color::green ), "[{}] INFO: {}", timestamp, message );
        }

        template <typename... Args>
        static void console_error( fmt::format_string<Args...> format, Args&&... args ) noexcept {
            auto timestamp = current_time();
            auto message = fmt::format( format, std::forward<Args>( args )... );
            fmt::print( fmt::fg( fmt::color::rosy_brown ), "[{}] ERROR: {}", timestamp, message );
        }

        template <typename... Args>
        static void console_info( fmt::format_string<Args...> format, Args&&... args ) noexcept {
            auto timestamp = current_time();
            auto message = fmt::format( format, std::forward<Args>( args )... );
            fmt::print( fmt::fg( fmt::color::green_yellow ), "[{}] INFO: {}", timestamp, message );
        }

    private:
        static std::string current_time() {
            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t( now );
            std::tm tm_now{};
#ifdef _WIN32
            localtime_s( &tm_now, &time_t_now );
#else
            localtime_r( &time_t_now, &tm_now );
#endif
            std::ostringstream oss;
            oss << std::put_time( &tm_now, "%Y-%m-%d %H:%M:%S" );
            return oss.str();
        }

#if ( _DEBUG )
        std::unique_ptr<fmt::ostream> file;
#endif
    };

#if ( _DEBUG )
    #define LOG_ERROR( logger, fmt, ... ) logger.log_error( FMT_STRING( fmt ), __VA_ARGS__ )
    #define LOG_INFO( logger, fmt, ... ) logger.log_info( FMT_STRING( fmt ), __VA_ARGS__ )
    #define CONSOLE_ERROR( fmt, ... ) logger::logger::console_error( FMT_STRING( fmt ), __VA_ARGS__ )
    #define CONSOLE_INFO( fmt, ... ) logger::logger::console_info( FMT_STRING( fmt ), __VA_ARGS__ )
#else
    #define LOG_ERROR( logger, fmt, ... )
    #define LOG_INFO( logger, fmt, ... )
    #define CONSOLE_ERROR( fmt, ... )
    #define CONSOLE_INFO( fmt, ... )
#endif

} // namespace logger
