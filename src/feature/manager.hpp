#pragma once

#include "feature.hpp"
#include <memory>
#include <optional>
#include <ranges>
#include <string_view>
#include <unordered_map>

namespace feature {
    class c_manager final {
    public:
        // Singleton pattern: returns the instance of the feature manager
        [[nodiscard]] static c_manager& instance() noexcept;

        // Deleted constructors and assignment operators to prevent copying/moving
        c_manager( const c_manager& ) = delete;
        c_manager& operator=( const c_manager& ) = delete;
        c_manager( c_manager&& ) = delete;
        c_manager& operator=( c_manager&& ) = delete;

        // Default constructor that initializes the manager with default features
        c_manager() noexcept;

        // Destructor that ensures proper cleanup
        ~c_manager() noexcept = default;

        // Adds a feature class to the manager (only default-constructible classes allowed)
        template <typename T>
            requires std::is_default_constructible_v<T>
        void add_class( const std::string_view& name ) noexcept;

        // Retrieves a feature by its name (returns nullptr if not found)
        [[nodiscard]] c_feature* get_feature_by_name( const std::string_view& name ) const noexcept;

        [[nodiscard]] std::shared_ptr<c_setting> get_settings_by_feature( const std::string_view& name, const std::string_view& setting_name ) noexcept;

        // Iterates and calls on_draw for all enabled features
        void on_draw() const noexcept;

        // Iterates and calls on_menu for all features
        void on_menu() const noexcept;

        // Updates the state of all features (enabled/disabled)
        void update() const noexcept;

    private:
        // Container for storing features by name
        std::unordered_map<std::string_view, std::unique_ptr<c_feature>> features;
    };

} // namespace feature
