#pragma once

#include <any>
#include <cassert>
#include <external/ImGui/imgui.h>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Represents a configurable setting with a name, description, and a value.
 */
class c_setting final {
public:
    /**
     * @brief Constructor for a c_setting.
     *
     * @param name The name of the setting.
     * @param description A short description of the setting.
     * @param value The value of the setting.
     */
    c_setting( std::string_view name, std::string_view description, const std::any& value ) noexcept
        : name_( name ), description_( description ), value_( value ) { }

    /**
     * @brief Gets the name of the setting.
     */
    [[nodiscard]] constexpr std::string_view get_name() const noexcept {
        return name_;
    }

    /**
     * @brief Gets the description of the setting.
     */
    [[nodiscard]] constexpr std::string_view get_description() const noexcept {
        return description_;
    }

    /**
     * @brief Gets the current value of the setting.
     */
    [[nodiscard]] const std::any& get_value() const noexcept {
        return value_;
    }

    /**
     * @brief Sets the value of the setting.
     *
     * @param val The new value to set for the setting.
     */
    void set_value( const std::any& val ) noexcept {
        value_ = val;
    }

private:
    std::string name_;        ///< The name of the setting
    std::string description_; ///< The description of the setting
    std::any value_;          ///< The value of the setting
};

/**
 * @brief A container class for managing a list of settings.
 */
class c_settings final {
public:
    using setting_ptr = std::shared_ptr<c_setting>;

    c_settings() noexcept = default;
    ~c_settings() noexcept = default;

    c_settings( const c_settings& ) = delete;
    c_settings& operator=( const c_settings& ) = delete;

    c_settings( c_settings&& ) noexcept = default;
    c_settings& operator=( c_settings&& ) noexcept = default;

    /**
     * @brief Initializes a setting and adds it to the global list.
     * @return A shared pointer to the created setting.
     */
    template <typename T>
        requires std::same_as<T, bool> || std::same_as<T, int32_t> || std::same_as<T, uint32_t> || std::same_as<T, float> || std::same_as<T, double> ||
                 std::same_as<T, std::string>
    [[nodiscard]] setting_ptr initialize( std::string_view name, std::string_view description, const T& value ) noexcept {
        if ( settings_map_.contains( std::string( name ) ) ) {
            return nullptr;
        }

        auto setting = std::make_shared<c_setting>( name, description, std::any( value ) );
        if ( !setting ) {
            return nullptr;
        }

        settings_vector_.push_back( setting );
        settings_map_[std::string( name )] = settings_vector_.size() - 1;

        return setting;
    }

    /**
     * @brief Gets all settings in the list.
     */
    [[nodiscard]] const std::vector<setting_ptr>& get_all() const noexcept {
        return settings_vector_;
    }

    /**
     * @brief Gets a specific setting by name.
     */
    [[nodiscard]] std::optional<setting_ptr> get( std::string_view name ) const noexcept {
        const auto it = settings_map_.find( std::string( name ) );
        if ( it == settings_map_.end() ) {
            return std::nullopt;
        }
        return settings_vector_[it->second];
    }

private:
    std::vector<setting_ptr> settings_vector_;                  ///< Vector of all settings
    std::unordered_map<std::string, std::size_t> settings_map_; ///< Map for fast lookup by setting name
};