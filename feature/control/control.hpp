#ifndef FEATURE_CONTROL_HPP
#define FEATURE_CONTROL_HPP

#include <feature.hpp>

#include <control/control_punch.hpp>

namespace feature::menu::control {
    class c_control final : public c_feature {
    public:
        explicit c_control() noexcept;
        ~c_control() noexcept override = default;

        void on_draw() noexcept final;
        void on_menu() noexcept final;
        void on_enabled() noexcept final;
        void on_disabled() noexcept final;

    private:
        std::shared_ptr<c_setting> selected_weapon;
    };
} // namespace feature::menu::control

#endif // !FEATURE_CONTROL_HPP
