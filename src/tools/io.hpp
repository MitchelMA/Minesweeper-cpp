#ifndef _IO_HPP
#define _IO_HPP

#include "keycodes.h"

namespace io
{
    struct ConsoleInputValue
    {
        int value = KEYCODE_UNSET;
        bool special = false;

        bool operator==(const ConsoleInputValue& other) const noexcept;
        bool operator==(const int& value) const noexcept;

        bool operator!=(const ConsoleInputValue& other) const noexcept;
        bool operator!=(const int& value) const noexcept;
    };

    class ConsoleInput
    {
        ConsoleInputValue last_value_;

    public:
        ConsoleInput() = default;

        void init() const noexcept;
        void restore() const noexcept;

        ConsoleInputValue get_input() noexcept;
        ConsoleInputValue get_last_input() const noexcept;
    };

    static ConsoleInput console_input;

    constexpr ConsoleInputValue key_arrow_up    {KEYCODE_ARROW_UP,    true};
    constexpr ConsoleInputValue key_arrow_right {KEYCODE_ARROW_RIGHT, true};
    constexpr ConsoleInputValue key_arrow_down  {KEYCODE_ARROW_DOWN,  true};
    constexpr ConsoleInputValue key_arrow_left  {KEYCODE_ARROW_LEFT,  true};

    constexpr ConsoleInputValue key_F1  {KEYCODE_F1,  true};
    constexpr ConsoleInputValue key_F2  {KEYCODE_F2,  true};
    constexpr ConsoleInputValue key_F3  {KEYCODE_F3,  true};
    constexpr ConsoleInputValue key_F4  {KEYCODE_F4,  true};
    constexpr ConsoleInputValue key_F5  {KEYCODE_F5,  true};
    constexpr ConsoleInputValue key_F6  {KEYCODE_F6,  true};
    constexpr ConsoleInputValue key_F7  {KEYCODE_F7,  true};
    constexpr ConsoleInputValue key_F8  {KEYCODE_F8,  true};
    constexpr ConsoleInputValue key_F9  {KEYCODE_F9,  true};
    constexpr ConsoleInputValue key_F10 {KEYCODE_F10, true};
    constexpr ConsoleInputValue key_F11 {KEYCODE_F11, true};
    constexpr ConsoleInputValue key_F12 {KEYCODE_F12, true};

    constexpr ConsoleInputValue key_insert {KEYCODE_INSERT, true};
    constexpr ConsoleInputValue key_home   {KEYCODE_HOME,   true};
    constexpr ConsoleInputValue key_pgup   {KEYCODE_PGUP,   true};
    constexpr ConsoleInputValue key_del    {KEYCODE_DEL,    true};
    constexpr ConsoleInputValue key_end    {KEYCODE_END,    true};
    constexpr ConsoleInputValue key_pgdn   {KEYCODE_PGDN,   true};

    constexpr ConsoleInputValue key_esc   {27, false};
    constexpr ConsoleInputValue key_space {32, false};

} // namespace io

#endif // !_IO_HPP