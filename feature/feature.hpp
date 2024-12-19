#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "settings.hpp"

#include <array>
#include <memory>
#include <string>

namespace feature {
    enum category_t {
        CONTROL,
        SETTINGS,
        APPEARANCE
    };

    static constexpr auto get_all_categories() noexcept {
        return std::array{ category_t::CONTROL, category_t::SETTINGS, category_t::APPEARANCE };
    }

    [[nodiscard]] std::string_view feature_type_to_string( category_t category ) noexcept;

    class c_feature {
    protected:
        category_t category;

        std::string_view name;
        std::string_view description;
        std::shared_ptr<c_setting> enabled_setting;
        std::unique_ptr<c_settings> settings_;

    public:
        explicit c_feature( std::string_view name, std::string_view description, const category_t category ) noexcept;
        virtual ~c_feature() noexcept = default;
        c_feature( const c_feature& ) = delete;
        c_feature& operator=( const c_feature& ) = delete;
        c_feature( c_feature&& ) = delete;
        c_feature& operator=( c_feature&& ) = delete;
    public:
        virtual void on_enable() noexcept = 0;
        virtual void on_disable() noexcept = 0;
        virtual void on_draw() noexcept = 0;
        virtual void on_menu() noexcept = 0;

    public:
        [[nodiscard]] bool is_enabled() const noexcept;
        [[nodiscard]] category_t get_category() const noexcept;
        [[nodiscard]] std::unique_ptr<c_settings>& get_settings() noexcept;
        [[nodiscard]] const std::string_view get_name() const noexcept;
        [[nodiscard]] const std::string_view get_description() const noexcept;


        bool draw_section = true;
    };
} // namespace feature

#endif // !FEATURE_HPP
