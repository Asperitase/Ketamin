#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../feature.hpp"

namespace feature::visual::control {
    class c_control final : public c_feature {
    public:
        explicit c_control() noexcept;
        ~c_control() noexcept override = default;
        void on_enable() noexcept final;
        void on_disable() noexcept final;
        void on_draw() noexcept final;
        void on_menu() noexcept final;

    private:
        std::shared_ptr<c_setting> current_weapon; 
    };
} // namespace feature::visual::control

#endif // !CONTROL_HPP
