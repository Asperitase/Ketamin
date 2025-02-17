#pragma once

#include <random>
#include <ranges>
#include <span>
#include <string>

namespace random_string {

    static std::string generate( size_t length = 10 ) {
        static constexpr std::string_view chars = "0123456789"
                                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                  "abcdefghijklmnopqrstuvwxyz";

        static std::random_device rd;
        static std::mt19937_64 generator( rd() );

        std::uniform_int_distribution<std::size_t> length_dist( 1, length );
        std::size_t length_ = length_dist( generator );

        std::string result;
        result.reserve( length_ );

        std::ranges::generate_n( std::back_inserter( result ), length_, []() {
            static std::uniform_int_distribution<std::size_t> char_dist( 0, chars.size() - 1 );
            return chars[char_dist( generator )];
        } );

        return result;
    }

    static std::string& get_stable() {
        static std::string cached_string = generate();
        return cached_string;
    }
} // namespace random_string