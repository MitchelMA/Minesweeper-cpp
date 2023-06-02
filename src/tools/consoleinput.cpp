#include "consoleinput.hpp"
#include <cstdio>
#include <unistd.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#include <conio.h>

#elif defined(__linux__)

#include <iostream>
#include <termios.h>

#endif // os-check

#pragma region Local Definitions

int hide_key() noexcept;
bool get_key(int& key) noexcept;

#pragma endregion

namespace io 
{
    #if defined(__linux__)

    constexpr int stdin_fileno = 0;
    static struct termios start_settings;

    #endif // linux-check

    bool
    ConsoleInputValue::operator==(
        const ConsoleInputValue& other
    ) const noexcept
    {
        if(other.special != special)
            return false;
        
        return other.value == value;
    }

    bool
    ConsoleInputValue::operator==(
        const int& other 
    ) const noexcept
    {
        return value == other;
    }

    bool
    ConsoleInputValue::operator!=(
        const ConsoleInputValue& other
    ) const noexcept
    {
        return !(*this == other);
    }

    bool
    ConsoleInputValue::operator!=(
        const int& other
    ) const noexcept
    {
        return !(*this == other);
    }

    void
    ConsoleInput::init()
    const noexcept
    {
    #if defined(__linux__)
       tcgetattr(stdin_fileno, &start_settings);
       struct termios new_settings = start_settings;

       new_settings.c_lflag &= ~ICANON;
       tcsetattr(stdin_fileno, TCSANOW, &new_settings);
    #endif // linux-check
    }

    void
    ConsoleInput::restore()
    const noexcept
    {
    #if defined(__linux__)
        tcsetattr(stdin_fileno, TCSANOW, &start_settings);
    #endif // linux-check
    }

    ConsoleInputValue
    ConsoleInput::get_input()
    noexcept
    {
        int key = KEYCODE_UNSET;
        bool special = get_key(key);
        last_value_ = {key, special};
        return last_value_;
    }

    ConsoleInputValue
    ConsoleInput::get_last_input()
    const noexcept
    {
        return last_value_;
    }

    const ConsoleInputValue&
    ConsoleInput::operator>>(
        ConsoleInputValue& out
    ) noexcept
    {
        out = get_input();
        return out;
    }

} // namespace io

#pragma region Local Implementations

bool
get_key(int& key)
noexcept
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    int c = 0;
    c = _getch();
    if(c && (c != 0xE0 && c != 0))
    {
        key = c;
        return false;
    }

    key = _getch();
    return true;

#elif defined(__linux__)

    int a=0, b=0;
    a = hide_key();
    if(a != 27)
    {
        key = a;
        return false;
    }

    b = hide_key();
    if(b != 91)
    {
        key = a;
        return false;
    }

    key = hide_key();
    return true;

#endif // os-check
}

int
hide_key()
noexcept
{
    int k=0;
    system("/bin/stty -echo");
    k = getchar();
    system("/bin/stty echo");
    return k;
}

#pragma endregion