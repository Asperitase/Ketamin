#pragma once

#include <any>
#include <cassert>
#include <external/ImGui/imgui.h>
#include <memory>
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
     * @param value The value of the setting, which can be of various types.
     */
    c_setting( std::string name, std::string description, const std::any& value ) noexcept
        : name( std::move( name ) ), description( std::move( description ) ), value( value ) { }

    /**
     * @brief Gets the name of the setting.
     *
     * @return The name of the setting.
     */
    [[nodiscard]] const std::string& get_name() const noexcept {
        return name;
    }

    /**
     * @brief Gets the description of the setting.
     *
     * @return The description of the setting.
     */
    [[nodiscard]] const std::string& get_description() const noexcept {
        return description;
    }

    /**
     * @brief Gets a reference to the value of the setting.
     *
     * @return A reference to the value of the setting.
     */
    std::any& get_value() noexcept {
        return value;
    }

    /**
     * @brief Sets the value of the setting.
     *
     * @param val The new value to set for the setting.
     */
    void set_value( const std::any& val ) noexcept {
        value = val;
    }

private:
    std::string name;        ///< The name of the setting.
    std::string description; ///< The description of the setting.
    std::any value;          ///< The value of the setting (can be any type).
};

/**
 * @brief A container class for managing a list of settings.
 */
class c_settings final {
public:
    /**
     * @brief Default constructor for the c_settings class.
     * Initializes empty vectors and reserves space for settings.
     */
    c_settings() noexcept {
        settings_map = std::unordered_map<std::string, std::size_t>(); // Mapping from setting name to index
    }

    /**
     * @brief Destructor for the c_settings class.
     * Ensures all settings are properly cleaned up.
     */
    ~c_settings() noexcept {
        for ( auto& setting : settings_vector )
            setting.reset(); // Reset all shared pointers in the vector to release memory
    }

    /**
     * @brief Initializes a setting and adds it to the global list.
     *
     * @param name The name of the setting.
     * @param description A description of the setting.
     * @param value The value of the setting (can be any type).
     * @return A shared pointer to the created setting.
     */
    template <typename T>
    std::shared_ptr<c_setting> initialize( const std::string& name, const std::string& description, const T& value ) noexcept {
        if ( settings_vector.size() == settings_vector.capacity() )
            settings_vector.reserve( settings_vector.capacity() * 2 );

        auto setting = std::make_shared<c_setting>( name, description, std::any( value ) );
        assert( setting && "Setting cannot be null." );
        settings_vector.push_back( setting );
        settings_map[setting->get_name()] = settings_vector.size() - 1;

        return setting;
    }

    /**
     * @brief Initializes a setting without adding it to the global list.
     * This is useful for local, temporary settings.
     *
     * @param name The name of the setting.
     * @param description A description of the setting.
     * @param value The value of the setting (can be any type).
     * @return A shared pointer to the created setting.
     */
    template <typename T>
    std::shared_ptr<c_setting> local_initialize( const std::string& name, const std::string& description, const T& value ) noexcept {
        return std::make_shared<c_setting>( name, description, std::any( value ) );
    }

    /**
     * @brief Gets all settings in the list.
     *
     * @return A constant reference to the vector containing all settings.
     */
    [[nodiscard]] const std::vector<std::shared_ptr<c_setting>>& get_all() const noexcept {
        return settings_vector;
    }

    /**
     * @brief Gets a specific setting by name.
     *
     * @param name The name of the setting to retrieve.
     * @return A constant reference to the shared pointer to the setting.
     */
    [[nodiscard]] const std::shared_ptr<c_setting>& get( const std::string& name ) const noexcept {
        const auto it = settings_map.find( name );
        if ( it == settings_map.end() )
            assert( false && "Setting not found." );

        return settings_vector[it->second];
    }

private:
    std::vector<std::shared_ptr<c_setting>> settings_vector;   ///< Vector of all settings.
    std::unordered_map<std::string, std::size_t> settings_map; ///< Map for fast lookup by setting name.
};
