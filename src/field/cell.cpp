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
        value_ = c.c.value_;
        neighbours_ = c.c.neighbours_;
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

    bool
    Cell::open()
    noexcept
    {
        if(this->is_flag(field::cell_flagged)) return false;
        this->value_ |= field::cell_opened;
        return true;
    }

    bool
    Cell::flag()
    noexcept
    {
        if(this->is_flag(field::cell_opened)) return false;
        this->value_ ^= field::cell_flagged;
        return true;
    }

} // namespace field
