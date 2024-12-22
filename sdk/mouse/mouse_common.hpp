#ifndef MOUSE_COMMON_HPP
#define MOUSE_COMMON_HPP

namespace sdk::mouse {
    enum class mouse_event_t : char {
        NONE = 0,
        PRESS = 1,
        RELEASE = 2,
        MOVE = 3,
        CLICK = 4
    };
} // namespace mouse

#endif // !define MOUSE_COMMON_HPP
