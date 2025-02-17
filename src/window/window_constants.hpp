#pragma once

#include <utils/random_string.hpp>

namespace window_constants {
    static auto window_class_name = random_string::get_stable().c_str();
    static auto window_title = random_string::get_stable().c_str();
} // namespace window_constants