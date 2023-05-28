#ifndef _IO_HPP
#define _IO_HPP

namespace io
{
    struct ConsoleInputValue
    {
        int value = -1;
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

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    constexpr ConsoleInputValue key_arrow_up    {72, true};
    constexpr ConsoleInputValue key_arrow_right {77, true};
    constexpr ConsoleInputValue key_arrow_down  {80, true};
    constexpr ConsoleInputValue key_arrow_left  {75, true};

    constexpr ConsoleInputValue key_F1  {59,  true};
    constexpr ConsoleInputValue key_F2  {60,  true};
    constexpr ConsoleInputValue key_F3  {61,  true};
    constexpr ConsoleInputValue key_F4  {62,  true};
    constexpr ConsoleInputValue key_F5  {63,  true};
    constexpr ConsoleInputValue key_F6  {64,  true};
    constexpr ConsoleInputValue key_F7  {65,  true};
    constexpr ConsoleInputValue key_F8  {66,  true};
    constexpr ConsoleInputValue key_F9  {67,  true};
    constexpr ConsoleInputValue key_F10 {68,  true};
    constexpr ConsoleInputValue key_F11 {133, true};
    constexpr ConsoleInputValue key_F12 {134, true};

    constexpr ConsoleInputValue key_insert {82, true};
    constexpr ConsoleInputValue key_home   {71, true};
    constexpr ConsoleInputValue key_pgup   {73, true};
    constexpr ConsoleInputValue key_del    {83, true};
    constexpr ConsoleInputValue key_end    {79, true};
    constexpr ConsoleInputValue key_pgdn   {81, true};


    #elif defined(__linux__)

    constexpr ConConsoleInputValues key_arrow_up    {65, true};
    constexpr ConConsoleInputValues key_arrow_right {67, true};
    constexpr ConConsoleInputValues key_arrow_down  {66, true};
    constexpr ConConsoleInputValues key_arrow_left  {68, true};

    #endif // os-check

    constexpr ConsoleInputValue key_esc   {27, false};
    constexpr ConsoleInputValue key_space {32, false};

} // namespace io

#endif // !_IO_HPP