#ifndef MOUSE_PARAMS_HPP
#define MOUSE_PARAMS_HPP

#include "mouse_common.hpp"

namespace sdk::mouse {
    typedef struct {
        mouse_event_t event; // Mouse event code
        char x;              // X-axis movement
        char y;              // Y-axis movement
        char wheel;          // Scroll wheel movement (up/down)
        char unk1;           // Reserved or unknown value
    } mouse_input;

    namespace offset {
        constexpr int move = 0x2a2010;
    }
} // namespace mouse

#endif // !MOUSE_PARAMS_HPP
