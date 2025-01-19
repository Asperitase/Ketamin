#ifndef FEATURE_OVERLAY_HPP
#define FEATURE_OVERLAY_HPP

#include <feature.hpp>

namespace feature::visual::overlay {
    class c_overlay final : public c_feature {
    public:
        explicit c_overlay() noexcept;
        ~c_overlay() noexcept override = default;

        void on_draw() noexcept final;
        void on_menu() noexcept final;
        void on_enabled() noexcept final;
        void on_disabled() noexcept final;
    };
} // namespace feature::visual::overlay

#endif // !FEATURE_OVERLAY_HPP
