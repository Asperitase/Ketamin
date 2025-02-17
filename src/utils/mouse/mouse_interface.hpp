#pragma once

#include "mouse_result.hpp"
#include "mouse_types.hpp"

namespace mouse {

    class i_mouse_device {
    public:
        virtual ~i_mouse_device() = default;

        [[nodiscard]] virtual result<bool> initialize() noexcept = 0;
        virtual void shutdown() noexcept = 0;
        [[nodiscard]] virtual result<bool> move( mouse_input input ) noexcept = 0;
        [[nodiscard]] virtual bool is_initialized() const noexcept = 0;
    };

} // namespace mouse