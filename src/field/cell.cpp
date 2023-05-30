#include "cell.hpp"

namespace field
{
    union conversion {
        Cell c;
        byte b;
    };

    Cell::Cell(byte byte)
    noexcept
    {
        conversion c = {.b = byte};
        *this = c.c;
    }

    byte
    Cell::to_byte()
    const noexcept
    {
        conversion c = {.c = *this};
        return c.b;
    }

    bool
    Cell::is_flag(std::uint32_t flag)
    const noexcept
    {
        return value_ & flag;
    }

} // namespace field
