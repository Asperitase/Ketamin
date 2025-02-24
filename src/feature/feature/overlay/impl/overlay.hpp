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
            explicit impl() noexcept;

            void on_draw() noexcept;
            void on_menu() noexcept;
            void on_enabled() noexcept;
            void on_disabled() noexcept;

        private:
            [[nodiscard( "Needed to check feature state" )]] bool is_enabled() const noexcept;

        private:
            overlay_context m_context;
            weapon_display_config_t m_config;
            header_config_t m_header_config;
            std::unique_ptr<header_panel> m_header_panel;
            std::unique_ptr<weapon_panel> m_weapon_panel;
            std::vector<panel*> m_panels;
        };

        std::unique_ptr<impl> m_impl;
    };

} // namespace feature::visual::overlay