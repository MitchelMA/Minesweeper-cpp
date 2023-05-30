#ifndef _PLAYFIELD_HPP
#define _PLAYFIELD_HPP

#include <cstddef>
#include "cell.hpp"

namespace field
{
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
}

#endif // !_PLAYFIELD_HPP