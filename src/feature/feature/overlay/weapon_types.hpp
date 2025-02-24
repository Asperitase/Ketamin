#pragma once

#include <string_view>

namespace feature::visual::overlay {
    template <typename T> concept type = std::is_enum_v<T>;

    /**
     * @brief Enumeration for weapon types
     */
    enum class weapon_type : std::uint8_t {
        none = 0,
        // Rifles
        ak47,
        lr300,
        mp5a4,

        // Semi Rifles
        sar,
        sks,
        m39,

        // SMGs
        weak_smg,
        smg,
        thompson,

        // Pistols
        m92,
        sap,
        heavy_revolver,
        revolver,
        python,
        prototype17,

        // Shotguns
        dbs,
        spas12,
        pomp_shotgun,
        pipe_shotgun,
        m4,

        // Snipers
        bolt,
        l96,

        // Other
        nailgun,
        minigun,
        grenade_launcher,
        m249,
        hmlmg,

        max_weapons
    };

    /**
     * @brief Enumeration for scope types
     */
    enum class scope_type : std::uint8_t {
        none = 0,
        handmade,
        holosight,
        x8,
        x16,
        max_scopes
    };

    /**
     * @brief Enumeration for module types
     */
    enum class module_type : std::uint8_t {
        none = 0,
        silencer,
        muzzle_brake,
        muzzle_boost,
        extended_mag,
        compressor,
        max_modules
    };

    namespace detail {
        /**
         * @brief Array of weapon names
         */
        static constexpr std::array weapon_names{ std::string_view{ "none" },
                                                  std::string_view{ "ak47" },
                                                  std::string_view{ "lr300" },
                                                  std::string_view{ "mp5a4" },
                                                  std::string_view{ "sar" },
                                                  std::string_view{ "sks" },
                                                  std::string_view{ "m39" },
                                                  std::string_view{ "weak_smg" },
                                                  std::string_view{ "smg" },
                                                  std::string_view{ "thompson" },
                                                  std::string_view{ "m92" },
                                                  std::string_view{ "sap" },
                                                  std::string_view{ "heavy_revolver" },
                                                  std::string_view{ "revolver" },
                                                  std::string_view{ "python" },
                                                  std::string_view{ "prototype17" },
                                                  std::string_view{ "dbs" },
                                                  std::string_view{ "spas12" },
                                                  std::string_view{ "pomp_shotgun" },
                                                  std::string_view{ "pipe_shotgun" },
                                                  std::string_view{ "m4" },
                                                  std::string_view{ "bolt" },
                                                  std::string_view{ "l96" },
                                                  std::string_view{ "nailgun" },
                                                  std::string_view{ "minigun" },
                                                  std::string_view{ "grenade_launcher" },
                                                  std::string_view{ "m249" },
                                                  std::string_view{ "hmlmg" } };

        /**
         * @brief Array of scope names
         */
        static constexpr std::array scope_names{ std::string_view{ "none" }, std::string_view{ "handmade" }, std::string_view{ "holosight" },
                                                 std::string_view{ "8x" }, std::string_view{ "16x" } };

        /**
         * @brief Array of module names
         */
        static constexpr std::array module_names{ std::string_view{ "none" },         std::string_view{ "silencer" },
                                                  std::string_view{ "muzzle_brake" }, std::string_view{ "muzzle_boost" },
                                                  std::string_view{ "extended_mag" }, std::string_view{ "compressor" } };

        static_assert( std::size( weapon_names ) == static_cast<size_t>( weapon_type::max_weapons ), "weapon_names size must match weapon_type enum" );
        static_assert( std::size( scope_names ) == static_cast<size_t>( scope_type::max_scopes ), "scope_names size must match scope_type enum" );
        static_assert( std::size( module_names ) == static_cast<size_t>( module_type::max_modules ), "module_names size must match module_type enum" );

        template <type T>
        constexpr bool is_valid_index( T type, std::span<const std::string_view> arr ) noexcept {
            return static_cast<size_t>( type ) < arr.size();
        }
    } // namespace detail

    /**
     * @brief Get string representation of a weapon type
     */
    template <type T>
    [[nodiscard]] constexpr std::string_view to_string( T type, std::span<const std::string_view> arr ) noexcept {
        return detail::is_valid_index( type, arr ) ? arr[static_cast<size_t>( type )] : arr[0];
    }


    struct weapon_data_t {
        weapon_type weapon{ weapon_type::none };
        scope_type scope{ scope_type::none };
        module_type module{ module_type::none };

        /**
         * @brief Check if item is not none
         * @tparam T Type of enum (weapon_type, scope_type, or module_type)
         * @param item Item to check
         * @return true if item is not none, false otherwise
         */
        template <type T>
        [[nodiscard]] constexpr bool has_item( const T item ) const noexcept {
            if constexpr ( std::is_same_v<T, weapon_type> ) {
                return item != weapon_type::none;
            } else if constexpr ( std::is_same_v<T, scope_type> ) {
                return item != scope_type::none;
            } else if constexpr ( std::is_same_v<T, module_type> ) {
                return item != module_type::none;
            }
            return false;
        }

        /**
         * @brief Check if item is not none and return specified value
         * @tparam T Type of enum (weapon_type, scope_type, or module_type)
         * @tparam ret_type Type of return value
         * @param item Item to check
         * @param value Value to return if item is valid
         * @return value if item is not none, default_value otherwise
         */
        template <type T, typename ret_type>
            requires std::is_arithmetic_v<ret_type>
        [[nodiscard]] constexpr ret_type additional_height( const T item, const ret_type value ) const noexcept {
            if constexpr ( std::is_same_v<T, weapon_type> ) {
                return ( item != weapon_type::none ) ? value : ret_type{ 0 };
            } else if constexpr ( std::is_same_v<T, scope_type> ) {
                return ( item != scope_type::none ) ? value : ret_type{ 0 };
            } else if constexpr ( std::is_same_v<T, module_type> ) {
                return ( item != module_type::none ) ? value : ret_type{ 0 };
            }
            return ret_type{ 0 };
        }
    };
} // namespace feature::visual::overlay