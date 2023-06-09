#ifndef _DIRIO_IPP
#define _DIRIO_IPP

namespace io
{
    template <typename ...>
    std::string join(std::string first)
    {
        return first;
    }

    template <typename ...R>
    std::string join(std::string first, R... remainder)
    {
        return first + seperator + join(remainder...);
    }
} // namespace io

#endif // !_DIRIO_IPP