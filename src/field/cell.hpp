#ifndef _CELL_HPP
#define _CELL_HPP

#include <cstdint>

namespace field
{

    constexpr std::uint32_t cell_opened  = 0x0001;
    constexpr std::uint32_t cell_bomb    = 0x0002;
    constexpr std::uint32_t cell_flagged = 0x0004;

    using byte = unsigned char;

    struct Cell
    {
        std::uint32_t value_ : 3;
        std::uint32_t neighbours_ : 4;

        Cell() = default;
        Cell(std::uint32_t value, std::uint32_t neighbours) noexcept :
            value_(value), neighbours_(neighbours) {};
        explicit Cell(byte value) noexcept;

        [[nodiscard("Returned byte is encouraged to be used.")]]
        byte to_byte() const noexcept;
        [[nodiscard("Returned boolean is encouraged to be used.")]]
        bool is_flag(std::uint32_t flag) const noexcept;
    };

} // namespace field

#endif // !_CELL_HPP