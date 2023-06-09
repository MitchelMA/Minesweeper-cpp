#ifndef _PLAYFIELD_HPP
#define _PLAYFIELD_HPP

#include <cstddef>
#include <string>
#include <memory>

#include "../tools/Result/result.hpp"
#include "cell.hpp"

#define STAND_FIELD_SIZE 30
#define STAND_BOMB_PERCENTAGE 10

namespace field
{
    struct Playfield
    {
        bool gameover;
        std::uint32_t bombpercentage;
        std::size_t seed;
        std::size_t size;
        std::size_t caret_x;
        std::size_t caret_y;
        // Cell** cells;
        std::unique_ptr<std::unique_ptr<Cell[]>[]> cells;

        static tools::Result<std::unique_ptr<Playfield>> from_file(std::string file_name) noexcept;
        int set_cells(byte* bytes, std::size_t byte_count) noexcept;
        void set_cells() noexcept;
        void display() const noexcept;
    };
}

#endif // !_PLAYFIELD_HPP