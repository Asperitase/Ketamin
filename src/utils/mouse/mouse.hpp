#pragma once

#include "mouse_interface.hpp"
#include <memory>

namespace mouse {

    class mouse final : public i_mouse_device {
    public:
        mouse() noexcept;
        ~mouse() noexcept override;

        mouse( const mouse& ) = delete;
        mouse& operator=( const mouse& ) = delete;
        mouse( mouse&& ) noexcept = default;
        mouse& operator=( mouse&& ) noexcept = default;

        [[nodiscard]] static mouse& instance() noexcept;

        [[nodiscard]] result<bool> initialize() noexcept override;
        void shutdown() noexcept override;
        [[nodiscard]] result<bool> move( mouse_input input ) noexcept;
        [[nodiscard]] bool is_initialized() const noexcept override;

    private:
        class impl;
        std::unique_ptr<impl> pimpl_;
    };

} // namespace mouse