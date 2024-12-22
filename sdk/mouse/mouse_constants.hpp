#ifndef MOUSE_CONSTANTS_HPP
#define MOUSE_CONSTANTS_HPP

#include <array>

namespace sdk::mouse {
    using char_t = const wchar_t*;

    static constexpr std::array<char_t, 2> device_names = { L"\\??\\ROOT#SYSTEM#0002#{1abc05c0-c378-41b9-9cef-df1aba82b015}",
                                                            L"\\??\\ROOT#SYSTEM#0001#{1abc05c0-c378-41b9-9cef-df1aba82b015}" };

} // namespace mouse

#endif // !MOUSE_CONSTANTS_HPP
