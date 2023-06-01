#include "dirio.hpp"

#include <Shlwapi.h>
#include <stdlib.h>
#pragma comment(lib, "shlwapi.lib")

#include <cstdlib>

#if defined(__linux__)
    #include <libgen.h>
    #include <unistd.h>
#endif // linux-check

char* GetExcecutableDir(char* dest, std::size_t dest_size);

namespace io
{

    char* get_executing_dir()
    {
        static char dest[_MAX_PATH];
        return GetExcecutableDir(dest, _MAX_PATH);
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