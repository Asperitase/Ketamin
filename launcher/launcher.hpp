#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <memory>

namespace global {
    class c_launcher final {
    public:
        explicit c_launcher() noexcept = default;
        c_launcher( const c_launcher& ) = delete;
        c_launcher& operator=( const c_launcher& ) = delete;
        c_launcher( c_launcher&& ) = delete;
        c_launcher& operator=( c_launcher&& ) = delete;
        ~c_launcher() noexcept = default;

        [[nodiscard]] static c_launcher& instance() noexcept;

        int start() const noexcept;
    };
} // namespace global

#endif // LAUNCHER_HPP