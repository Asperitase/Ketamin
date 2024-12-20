#ifndef SDK_COMMON_HPP
#define SDK_COMMON_HPP

namespace sdk::common {
    enum class mouse_event : char {
        NONE = 0,
        PRESS = 1,
        RELEASE = 2,
        MOVE = 3,
        CLICK = 4
    };

    typedef struct {
        mouse_event event;  // Mouse event code
        char x;              // X-axis movement
        char y;              // Y-axis movement
        char wheel;          // Scroll wheel movement (up/down)
        char unk1;           // Reserved or unknown value
    } mouse_input;

} // namespace sdk::common

#endif // !SDK_COMMON_HPP
