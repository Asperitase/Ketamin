#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <memory>

namespace global {
    class c_launcher final {
        int _argc = 0;
        char** _argv = nullptr;

    public:
        explicit c_launcher( int argc, char* argv[] ) noexcept;
        c_launcher( const c_launcher& ) = delete;
        c_launcher& operator=( const c_launcher& ) = delete;
        c_launcher( c_launcher&& ) = delete;
        c_launcher& operator=( c_launcher&& ) = delete;
        ~c_launcher() noexcept;

        [[nodiscard]] static std::unique_ptr<c_launcher> create( int argc, char* argv[] ) noexcept;

        int start() const noexcept;
    };
} // namespace global

#endif // LAUNCHER_HPP