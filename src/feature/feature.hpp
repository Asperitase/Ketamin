#pragma once

#include "settings.hpp"

#include <memory>

#include "category_list.hpp"

namespace feature {
    /**
     * @brief Base class representing a feature in the system.
     */
    class c_feature {
    protected:
        category_t category;                        ///< The category the feature belongs to.
        std::string name;                           ///< The name of the feature.
        std::string description;                    ///< The description of the feature.
        std::shared_ptr<c_setting> enabled_setting; ///< Shared setting for enabling/disabling the feature.
        std::unique_ptr<c_settings> settings;       ///< Unique pointer to the feature's settings.

    public:
        /**
         * @brief Constructor for the c_feature class.
         *
         * @param name The name of the feature.
         * @param description A short description of the feature.
         * @param category The category the feature belongs to.
         */
        explicit c_feature( std::string name, std::string description, category_t category ) noexcept;

        virtual ~c_feature() noexcept = default;

        c_feature( const c_feature& ) = delete;            ///< Delete copy constructor to prevent copying.
        c_feature& operator=( const c_feature& ) = delete; ///< Delete copy assignment operator.
        c_feature( c_feature&& ) = delete;                 ///< Delete move constructor.
        c_feature& operator=( c_feature&& ) = delete;      ///< Delete move assignment operator.

        /**
         * @brief Draws the feature (for example, rendering on the screen).
         */
        virtual void on_draw() noexcept = 0;

        /**
         * @brief Displays the feature's menu options.
         */
        virtual void on_menu() noexcept = 0;

        /**
         * @brief Executes logic when the feature is enabled.
         *
         * This method is called once when the feature is turned on, allowing
         * initialization or activation-specific logic to run.
         */
        virtual void on_enabled() noexcept = 0;

        /**
         * @brief Executes logic when the feature is disabled.
         *
         * This method is called once when the feature is turned off, allowing
         * cleanup or deactivation-specific logic to run.
         */
        virtual void on_disabled() noexcept = 0;

        /**
         * @brief Checks if the feature is enabled.
         *
         * @return True if the feature is enabled, false otherwise.
         */
        [[nodiscard]] bool is_enabled() const noexcept;

        /**
         * @brief Gets the category of the feature.
         *
         * @return The category of the feature.
         */
        [[nodiscard]] category_t get_category() const noexcept;

        /**
         * @brief Gets the settings associated with the feature.
         *
         * @return A reference to the settings of the feature.
         */
        [[nodiscard]] std::unique_ptr<c_settings>& get_settings() noexcept;

        /**
         * @brief Gets the name of the feature.
         *
         * @return The name of the feature.
         */
        [[nodiscard]] const std::string& get_name() const noexcept;

        /**
         * @brief Gets the description of the feature.
         *
         * @return The description of the feature.
         */
        [[nodiscard]] const std::string& get_description() const noexcept;
    };
} // namespace feature
