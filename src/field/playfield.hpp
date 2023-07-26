#ifndef _PLAYFIELD_HPP
#define _PLAYFIELD_HPP

#include <cstddef>
#include <string>
#include <memory>

#include "../tools/Result/result.hpp"
#include "../tools/consoleinput.hpp"
#include "cell.hpp"

#define STAND_FIELD_SIZE 30
#define STAND_BOMB_PERCENTAGE 10

#define FIELD_PRINT_X "1"
#define FIELD_PRINT_Y "3"

namespace field
{
    struct Playfield
    {
    public:
        int exit_code;
        bool gameover;
        std::uint32_t bombpercentage;
        std::size_t seed;
        std::size_t size;
        std::size_t caret_x;
        std::size_t caret_y;
        std::unique_ptr<std::unique_ptr<Cell[]>[]> cells;

        static tools::Result<std::unique_ptr<Playfield>> from_file(std::string file_name) noexcept;
        [[nodiscard]]
        tools::Result<int> write_to_file(std::string file_name, bool save_cells) const noexcept;
        int set_cells(byte* bytes, std::size_t byte_count) noexcept;
        void set_cells() noexcept;
        [[nodiscard]]
        std::string as_text() const noexcept;
        [[nodiscard]]
        std::string peek() const noexcept;
        void open_series(std::size_t x, std::size_t y) noexcept;
        [[nodiscard]]
        bool eval() const noexcept;
        /**
         * Main-loop of the game
         * @return
         * Reasons for exiting:\n
         * 1: User-requested exit.\n
         * 2: Game-over.\n
         * 3: Game-win.\n
         * 4: Error.
         */
        [[nodiscard]]
        int run() noexcept;

    private:
        /**
         * Handles exit-conditions:\n
         * @param input_value
         * @return
         * 0: Nothing.\n
         * 1: User-requested exit.\n
         * 2: Game-over.\n
         * 3: Game-win.\n
         */
        [[nodiscard]]
        int handle_exit(const io::ConsoleInputValue& input_value) const noexcept;
    };
}

#endif // !_PLAYFIELD_HPP