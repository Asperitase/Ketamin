#pragma once

#include <feature/feature.hpp>
#include <feature/feature/overlay/components/header_panel.hpp>
#include <feature/feature/overlay/components/weapon_panel.hpp>
#include <feature/feature/overlay/overlay_types.hpp>
#include <memory>
#include <vector>

namespace feature::visual::overlay {

    class overlay : public c_feature {
    public:
        explicit overlay() noexcept;
        ~overlay() noexcept override = default;

        overlay( const overlay& ) = delete;
        overlay& operator=( const overlay& ) = delete;

        overlay( overlay&& ) noexcept = default;
        overlay& operator=( overlay&& ) noexcept = default;

        void on_draw() noexcept override;
        void on_menu() noexcept override;
        void on_enabled() noexcept override;
        void on_disabled() noexcept override;

    private:
        std::shared_ptr<c_setting> selected_weapon;
        std::shared_ptr<c_setting> selected_scope;
        std::shared_ptr<c_setting> selected_module;

    private:
        class impl {
        public:
            struct config_t {
                std::shared_ptr<c_setting> weapon;
                std::shared_ptr<c_setting> scope;
                std::shared_ptr<c_setting> module;
                std::shared_ptr<c_setting> enabled;
            };

            explicit impl( const config_t& config ) noexcept;

            void draw() noexcept;
            void show_menu() noexcept;
            void enable() noexcept;
            void disable() noexcept;

        private:
            [[nodiscard]] bool is_enabled() const noexcept;

        private:
            std::shared_ptr<c_setting> m_enabled;
            std::shared_ptr<c_setting> m_weapon;
            std::shared_ptr<c_setting> m_scope;
            std::shared_ptr<c_setting> m_module;

        private:
            overlay_context m_context;
            std::unique_ptr<c_header_panel> m_header_panel;
            std::unique_ptr<c_weapon_panel> m_weapon_panel;
            std::vector<c_panel*> m_panels;
        };

        std::unique_ptr<impl> m_impl;
    };

} // namespace feature::visual::overlay