#include "dirio.hpp"
#include <cstdlib>
#include <sstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    #include <Shlwapi.h>
    #pragma comment(lib, "shlwapi.lib")

#elif defined(__linux__)

    #include <libgen.h>
    #include <unistd.h>

#ifndef _MAX_PATH
    #define _MAX_PATH 260
#endif // _MAX_PATH

#endif // os-check

char* GetExcecutableDir(char* dest, std::size_t dest_size);

namespace io
{

    char* get_executing_dir()
    {
        static char dest[_MAX_PATH];
        return GetExcecutableDir(dest, _MAX_PATH);
    }

    std::string join(std::string* params, std::size_t param_count)
    {
        if(params == NULL)
            return "";

        std::stringstream ss;
        ss << *params;
        for(std::size_t i = 1; i < param_count; i++)
            ss << seperator << params[i];

        return ss.str();
    }

    std::string join(const char* params[], std::size_t param_count)
    {
        if(params == NULL)
            return "";

        std::stringstream ss;
        ss << *params;
        for(std::size_t i = 1; i< param_count; i++)
            ss << seperator << params[i];

        return ss.str();
    }

} // namespace io

char* GetExcecutableDir(char* dest, std::size_t dest_size)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    DWORD length = GetModuleFileName(
        NULL,
        dest,
        dest_size
    );
    PathRemoveFileSpec(dest);

#elif defined(__linux__)

    ssize_t length = readlink("/proc/self/exe", dest, dest_size);
    if(length != -1)
        dest = dirname(dest);

#endif // os-check
    return dest;
}