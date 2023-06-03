#ifndef _IO_HPP
#define _IO_HPP

#include "keycodes.h"
#include <cstdio>
#include <cstdint>

#if defined(__linux__)
    #define _MAX_DEGREE_COUNT 8
#endif // linux-check

namespace io
{
    struct ConsoleInputValue
    {
        std::uint64_t value = KEYCODE_UNSET;

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

        bool special = false;

    #elif defined(__linux__)

        std::size_t degree = 1;

    #endif // os-check

        int get_value() const noexcept;
        bool is_special() const noexcept;

        bool operator==(const ConsoleInputValue& other) const noexcept;
        bool operator==(const std::uint64_t& value) const noexcept;

        bool operator!=(const ConsoleInputValue& other) const noexcept;
        bool operator!=(const std::uint64_t& value) const noexcept;
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

        const ConsoleInputValue& operator >> (ConsoleInputValue& out) noexcept;
    };

    static ConsoleInput console_input;

    constexpr ConsoleInputValue key_arrow_up    {KEYCODE_ARROW_UP};
    constexpr ConsoleInputValue key_arrow_right {KEYCODE_ARROW_RIGHT};
    constexpr ConsoleInputValue key_arrow_down  {KEYCODE_ARROW_DOWN};
    constexpr ConsoleInputValue key_arrow_left  {KEYCODE_ARROW_LEFT};

    constexpr ConsoleInputValue key_F1  {KEYCODE_F1};
    constexpr ConsoleInputValue key_F2  {KEYCODE_F2};
    constexpr ConsoleInputValue key_F3  {KEYCODE_F3};
    constexpr ConsoleInputValue key_F4  {KEYCODE_F4};
    constexpr ConsoleInputValue key_F5  {KEYCODE_F5};
    constexpr ConsoleInputValue key_F6  {KEYCODE_F6};
    constexpr ConsoleInputValue key_F7  {KEYCODE_F7};
    constexpr ConsoleInputValue key_F8  {KEYCODE_F8};
    constexpr ConsoleInputValue key_F9  {KEYCODE_F9};
    constexpr ConsoleInputValue key_F10 {KEYCODE_F10};
    constexpr ConsoleInputValue key_F11 {KEYCODE_F11};
    constexpr ConsoleInputValue key_F12 {KEYCODE_F12};

    constexpr ConsoleInputValue key_insert {KEYCODE_INSERT};
    constexpr ConsoleInputValue key_home   {KEYCODE_HOME};
    constexpr ConsoleInputValue key_pgup   {KEYCODE_PGUP};
    constexpr ConsoleInputValue key_del    {KEYCODE_DEL};
    constexpr ConsoleInputValue key_end    {KEYCODE_END};
    constexpr ConsoleInputValue key_pgdn   {KEYCODE_PGDN};

    constexpr ConsoleInputValue key_esc   {27, 1};
    constexpr ConsoleInputValue key_space {32, 1};

} // namespace io

#endif // !_IO_HPP