#include "playfield.hpp"
#include "cell.hpp"
#include <cstddef>

namespace field
{
    struct Cell
    {
        uint32_t value_ : 3;
        uint32_t neighbours_ : 4;
    };

    struct Playfield
    {
        bool gameover;
        std::uint32_t bombpercentage;
        std::uint32_t seed;
        std::size_t size;
        std::size_t caret_x;
        std::size_t caret_y;
        Cell** cells;
    };

} // namespace field
