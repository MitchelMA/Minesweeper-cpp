#include "consoleinput.hpp"
#include "keycodes.h"
#include <sys/types.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <limits>
#include <cstdint>
#include <unistd.h>
#include <sys/select.h>
#include <algorithm>

#endif // os-check

#pragma region Local Definitions

io::ConsoleInputValue get_key() noexcept;

#pragma endregion

namespace io 
{
    #if defined(__linux__)

    constexpr int stdin_fileno = 0;
    static struct termios start_settings;

    #endif // linux-check

    int
    ConsoleInputValue::get_value()
    const noexcept
    {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

        return value;

    #elif defined(__linux__)

        return values[degree-1];

    #endif // os-check
    }

    bool
    ConsoleInputValue::is_special()
    const noexcept
    {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

        return special;

    #elif defined(__linux__)

        return degree > 1;

    #endif // os-check
    }

    bool
    ConsoleInputValue::operator==(
        const ConsoleInputValue& other
    ) const noexcept
    {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    
        if(other.special != special)
            return false;
        
        return other.value == value;

#elif defined(__linux__)

    ssize_t biggest = std::max(degree, other.degree);
    for(ssize_t i = 0; i < biggest; i++)
        if(values[i] != other.values[i])
            return false;

    return true;

#endif // os-check
    }

    bool
    ConsoleInputValue::operator==(
        const int& other 
    ) const noexcept
    {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

        return value == other;

    #elif defined(__linux__)

        return values[degree-1] == other;

    #endif // os-check
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

       new_settings.c_lflag &= (~ICANON & ~ECHO);
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
        last_value_ = get_key();
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

io::ConsoleInputValue
get_key()
noexcept
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    int c = _getch();
    if(c && (c != 0xE0 && c != 0))
    {
        return io::ConsoleInputValue{c, false};
    }

    return io::ConsoleInputValue{_getch(), true};

#elif defined(__linux__)

    static unsigned char keys[_MAX_DEGREE_COUNT] = {
       0 
    };
    std::uint32_t c;
    fd_set set;
    struct timeval tv;
    tv.tv_sec  = std::numeric_limits<__time_t>::max();
    tv.tv_usec = 0;

    FD_ZERO(&set);
    FD_SET(io::stdin_fileno, &set);

    int res = select(io::stdin_fileno+1, &set, NULL, NULL, &tv);
    ssize_t degree = read(io::stdin_fileno, &keys, _MAX_DEGREE_COUNT);
    return io::ConsoleInputValue{
        keys[0], keys[1], keys[2], keys[3], keys[4], keys[5], keys[6],
        degree
    };


#endif // os-check
}
