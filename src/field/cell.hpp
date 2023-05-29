#ifndef _CELL_HPP
#define _CELL_HPP

#include <cstdint>

namespace field
{

    constexpr std::uint32_t cell_opened  = 0x0001;
    constexpr std::uint32_t cell_bomb    = 0x0002;
    constexpr std::uint32_t cell_flagged = 0x0003;


    using byte = unsigned char;

    struct Cell;

    byte celltb(Cell);
    Cell bytetc(byte);
    bool cell_is(const Cell& cell, std::uint32_t flag);
    std::uint32_t cell_n(const Cell& cell);

} // namespace field

#endif // !_CELL_HPP