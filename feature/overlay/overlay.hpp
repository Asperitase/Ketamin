#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include "../feature.hpp"

namespace feature::visual::overlay {

    class c_overlay final : public c_feature {
    public:
        explicit c_overlay() noexcept;
        ~c_overlay() noexcept override = default;
        void on_enable() noexcept final;
        void on_disable() noexcept final;
        void on_draw() noexcept final;
        void on_menu() noexcept final;
    };
} // namespace feature::visual::overlay

#endif // !OVERLAY_HPP
