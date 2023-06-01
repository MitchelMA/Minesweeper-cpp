#ifndef _DIRIO_HPP
#define _DIRIO_HPP

namespace io
{

    char* get_executing_dir();
    static char* exe_dir = get_executing_dir();
}

#endif // !_DIRIO_HPP