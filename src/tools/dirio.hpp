#ifndef _DIRIO_HPP
#define _DIRIO_HPP

#include <string>
#include <iostream>

namespace io
{

    char* get_executing_dir();
    static char* exe_dir = get_executing_dir();

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    constexpr char seperator = '\\';
    #elif defined(__linux__)
    constexpr char seperator = '/';
    #endif // os-check

    template <typename ...>
    std::string join(std::string first);

    template <typename ... R>
    std::string join(std::string first, R... remainder);

} // namespace io

#include "dirio.ipp"

#endif // !_DIRIO_HPP