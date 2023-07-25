#include <cmath>
#include <format>
#include <ctime>
#include <iostream>
#include <sstream>
#include "playfield.hpp"

static FILE* save_file;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    #define OPEN_SAVE_R fopen_s(&save_file, file_name.c_str(), "rb")
#elif defined(__linux__)
    #define OPEN_SAVE_R save_file = fopen(file_name.c_str(), "rb")
#endif // os-check
#define CLOSE_SAVE fclose(save_file)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    #define SCAN_BASE_FLAGS fscanf_s(save_file, "%zu %u %d", &field->size, &field->bombpercentage, &has_save)
#elif defined(__linux__)
    #define SCAN_BASE_FLAGS fscanf(save_file, "%zu %u %d", &field->size, &field->bombpercentage, &has_save)
#endif // os-check

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    #define SCAN_SEED fscanf_s(save_file, "%zu", &field->seed)
#elif defined(__linux__)
    #define SCAN_SEED fscanf(save_file, "%zu", &field->seed)
#endif // os-check

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    #define SCAN_CELLS fread_s(bytes.get(), field->size * field->size, 1, field->size * field->size, save_file)
#elif defined(__linux__)
    #define SCAN_CELLS fread(bytes.get(), 1, field->size * field->size, save_file)
#endif // os-check

#define FLAG_ESCAPE_CODE "\x1b[4m\x1b[97m\x1b[101m"

#define BOMB_ESCAPE_CODE "\x1b[97m\x1b[41m"

#define NON_BOMB_ESCAPE(OSTREAM, NEIGHBOUR_COUNT, ESCAPE_ARRAY)                  \
    do {                                                                         \
        OSTREAM << ESCAPE_ARRAY[NEIGHBOUR_COUNT];                                \
        OSTREAM << (NEIGHBOUR_COUNT == 0 ? ' ' : (char) (NEIGHBOUR_COUNT + 48)); \
        OSTREAM << "\x1b[0m";                                                    \
    } while(0)

void cell_set_bomb(field::Playfield& field, std::size_t x, std::size_t y) noexcept;

namespace field
{

    tools::Result<std::unique_ptr<Playfield>> 
    Playfield::from_file(
        std::string file_name
    ) noexcept
    {
        OPEN_SAVE_R;

        if(save_file == nullptr)
            return new std::runtime_error(
                std::format("Couldn't open file \"{}\"", file_name));
        
        auto field = std::make_unique<Playfield>();

        int has_save = 0;
        if(SCAN_BASE_FLAGS == EOF)
        {
            CLOSE_SAVE;
            return new std::runtime_error("Found data in incorrect format");
        }

        if(!has_save)
        {
            CLOSE_SAVE;
            return field;
        }

        if(SCAN_SEED == EOF)
        {
            CLOSE_SAVE;
            return new std::runtime_error("No seed was found where seed was expected");
        }

        auto bytes = std::make_unique<byte[]>(field->size * field->size);
        auto read_count = SCAN_CELLS;
        CLOSE_SAVE;

        if(read_count != field->size * field->size)
            return new std::runtime_error(
                std::format(
                    "Could only read {} bytes of data where there should have been {} bytes of data", 
                    read_count, field->size * field->size
                )
            );

        field->set_cells(bytes.get(), field->size*field->size);

        return field;
    }

    int
    Playfield::set_cells(byte* bytes, std::size_t byte_count)
    noexcept
    {
        if(size * size != byte_count)
            return 1;

        if(cells.get() != nullptr)
            return 1;
            
        cells = std::make_unique<std::unique_ptr<Cell[]>[]>(size);
        for(std::size_t i = 0; i < size; i++)
        {
            cells[i] = std::make_unique<Cell[]>(size);

            for(std::size_t j = 0; j < size; j++)
            {
                std::size_t index = i * size + j;
                cells[i][j] = field::Cell(bytes[index]);
            }
        }

       return 0;
    }

    void
    Playfield::set_cells()
    noexcept
    {
        seed == 0 && (seed = time(nullptr));
        srand((unsigned int)seed);
        std::size_t bomb_count = (std::size_t)(((float)bombpercentage / 100) * (size * size));

        if(cells.get() == nullptr)
        {
            cells = std::make_unique<std::unique_ptr<Cell[]>[]>(size);
            for(std::size_t i = 0; i < size; i++)
                cells[i] = std::make_unique<Cell[]>(size);
        }

        for(std::size_t i = 0; i < bomb_count;)
        {
            std::size_t rand_x = rand() % size;
            std::size_t rand_y = rand() % size;

            auto cell = cells[rand_y][rand_x];

            if(cell.is_flag(field::cell_bomb))
                continue;

            cell_set_bomb(*this, rand_x, rand_y);
            i++;
        }
    }

    std::string
    Playfield::as_text() const noexcept
    {
        std::ostringstream buffer;
        static const std::string ANSI_COLOURS[9] = {
                "\x1b[0m",
                "\x1b[34m",
                "\x1b[32m",
                "\x1b[31m",
                "\x1b[35m",
                "\x1b[90m",
                "\x1b[36m",
                "\x1b[2m",
                "\x1b[33m"
        };

        for(std::size_t y = 0; y < size; y++)
        {
            for(std::size_t x = 0; x < size; x++)
            {
                bool chosen = x == caret_x && y == caret_y;
                buffer << (chosen ? '[' : ' ');
                Cell& cell = cells[y][x];

                if(cell.is_flag(field::cell_flagged))
                {
                    buffer << FLAG_ESCAPE_CODE << "f\x1b[0m";
                }
                else if(cell.is_flag(field::cell_opened))
                {
                    if(cell.is_flag(field::cell_bomb))
                    {
                        buffer << BOMB_ESCAPE_CODE << "*\x1b[0m";
                    }
                    else
                    {
                        std::uint32_t neighbour_count = cell.neighbours_;
                        NON_BOMB_ESCAPE(buffer, neighbour_count, ANSI_COLOURS);
                    }
                }
                else
                {
                    buffer << '.';
                }

                buffer << (chosen ? ']' : ' ');
            }
            if(y < size - 1)
                buffer << "\n";
        }

        return buffer.str();
    }

} // namespace field

void
cell_set_bomb(field::Playfield& field, std::size_t x, std::size_t y)
noexcept
{
    if(x < 0 || y < 0 || x >= field.size || y >= field.size)
        return;

    auto& cell = field.cells[y][x];

    cell.value_ |= field::cell_bomb;
    if (x > 0)
    {
        field.cells[y][x - 1].neighbours_++;
    }
    if (x < field.size - 1)
    {
        field.cells[y][x + 1].neighbours_++;
    }

    if (y > 0)
    {
        field.cells[y - 1][x].neighbours_++;
    }
    if (y < field.size - 1)
    {
        field.cells[y + 1][x].neighbours_++;
    }

    if (x > 0 && y > 0)
    {
        field.cells[y - 1][x - 1].neighbours_++;
    }
    if (x < field.size - 1 && y > 0)
    {
        field.cells[y - 1][x + 1].neighbours_++;
    }
    if (x > 0 && y < field.size - 1)
    {
        field.cells[y + 1][x - 1].neighbours_++;
    }
    if (x < field.size - 1 && y < field.size - 1)
    {
        field.cells[y + 1][x + 1].neighbours_++;
    }
}