#include "cell.hpp"

namespace field
{

    struct Cell
    {
        std::uint32_t value_ : 3;
        std::uint32_t neighbours_ : 4;
    };

    union conversion {
        Cell c;
        byte b;
    };

    byte celltb(Cell cell)
    {
        conversion c = {.c = cell};
        return c.b;
    }

    Cell bytetc(byte byte)
    {
        conversion c = {.b = byte};
        return c.c;
    }

    bool cell_is(const Cell& cell, std::uint32_t flag)
    {
        return cell.value_ & flag;
    }

    std::uint32_t cell_n(const Cell& cell)
    {
        return cell.neighbours_;
    }

} // namespace field
