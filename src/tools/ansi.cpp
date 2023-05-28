#include "ansi.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#include <windows.h>

#endif // win-check

#pragma region Local Definitions
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
void _get_h();
#endif // win-check
#pragma endregion Local Definitions

namespace ansi
{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    static DWORD _stdout_start_mode = 0;
    static DWORD _stdout_mode = 0;
    static HANDLE _stdout_handle = 0;

#endif // win-check


    unsigned long
    enable_ansi()
    {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
        _get_h();

        if(_stdout_handle == INVALID_HANDLE_VALUE)
            return GetLastError();

        if(!GetConsoleMode(_stdout_handle, &_stdout_start_mode))
            return GetLastError();

        _stdout_mode = _stdout_start_mode;

        _stdout_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if(!SetConsoleMode(_stdout_handle, _stdout_mode))
            return GetLastError();

    #endif // win-check

        return 0;
    }

    unsigned long
    disable_ansi()
    {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
        if(!SetConsoleMode(_stdout_handle, _stdout_start_mode))
            return GetLastError();
    #endif // win-check

        return 0;
    }

} // namespace ansi

#pragma region Local Implementations

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
void
_get_h()
{
    if(ansi::_stdout_handle != 0 && ansi::_stdout_handle != INVALID_HANDLE_VALUE)
        return;
    
    ansi::_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}
#endif // win-check

#pragma endregion Local Implementations