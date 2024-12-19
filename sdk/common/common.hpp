#ifndef SDK_COMMON_HPP
#define SDK_COMMON_HPP

namespace sdk::common {
    enum class mouse_button : char {
        none = 0,
        press = 1,
        release = 2,
        move = 3,
        click = 4
    };

    typedef struct {
        mouse_button button; // Mouse button code (pressed or released)
        char x;              // X-axis movement
        char y;              // Y-axis movement
        char wheel;          // Scroll wheel movement (up/down)
        char unk1;           // Reserved or unknown value
    } mouse_input;

} // namespace sdk::common

#endif // !SDK_COMMON_HPP
