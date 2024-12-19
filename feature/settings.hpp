#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <ImGui/imgui.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

class c_setting {
public:
    c_setting( std::string name, std::string description, const std::variant<bool, int, float, std::string, ImColor>& value ) noexcept
        : name( std::move( name ) ), description( std::move( description ) ), value( value ) { }

    [[nodiscard]] const std::string& get_name() const noexcept {
        return name;
    }

    [[nodiscard]] const std::string& get_description() const noexcept {
        return description;
    }

    std::variant<bool, int, float, std::string, ImColor>& get_value() noexcept {
        return value;
    }

    void set_value( const std::variant<bool, int, float, std::string, ImColor>& val ) noexcept {
        value = val;
    }

private:
    std::string name;
    std::string description;
    std::variant<bool, int, float, std::string, ImColor> value;
};

class c_settings {
public:
    c_settings() noexcept {
        settings_vector.reserve( 100 );
        settings_map = std::unordered_map<std::string, std::size_t>();
    }

    ~c_settings() noexcept {
        for ( auto& setting : settings_vector ) {
            setting.reset();
        }
    }

    void add_settings( const std::shared_ptr<c_setting>& setting ) noexcept {
        settings_vector.push_back( setting );
        settings_map[settings_vector.back()->get_name()] = settings_vector.size() - 1;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<c_setting>>& get_settings() const noexcept {
        return settings_vector;
    }

    [[nodiscard]] const std::shared_ptr<c_setting>& get_setting( const std::string& name ) const noexcept {
        const auto it = settings_map.find( name );
        if ( it == settings_map.end() )
            assert( false && "Setting not found." );

        return settings_vector[it->second];
    }

private:
    std::vector<std::shared_ptr<c_setting>> settings_vector;
    std::unordered_map<std::string, std::size_t> settings_map;
};

#endif // !1
