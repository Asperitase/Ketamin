// category_enum.hpp
#pragma once

#include <array>
#include <string_view>

namespace feature {

    enum class category_t {
        VISUAL ///< Visual-related features.
    };

    /**
     * @brief Returns the string representation of a feature category.
     *
     * @param category The category to convert.
     * @return A string_view corresponding to the category.
     */
    constexpr std::string_view category_to_string( category_t category ) noexcept {
        switch ( category ) {
        case category_t::VISUAL:
            return "Visual";
        }
    }

    /**
     * @brief Returns a list of all feature categories.
     *
     * @return A constant array containing all possible feature categories.
     */
    static constexpr auto get_all_categories() noexcept {
        return std::array{ category_t::VISUAL };
    }

} // namespace feature
