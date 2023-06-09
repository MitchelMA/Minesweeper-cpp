#include <cstddef>
#include <format>
#include <memory>
#include "playfield.hpp"
#include "cell.hpp"

static FILE* save_file;

#define OPEN_SAVE_R fopen_s(&save_file, file_name.c_str(), "rb")
#define CLOSE_SAVE fclose(save_file)

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
        if(fscanf_s(save_file, "%zu %u %d", &field->size, &field->bombpercentage, &has_save) == EOF)
        {
            CLOSE_SAVE;
            return new std::runtime_error("Found data in incorrect format");
        }

        if(!has_save)
        {
            CLOSE_SAVE;
            return field;
        }

        if(fscanf_s(save_file, "%u", &field->seed) == EOF)
        {
            CLOSE_SAVE;
            return new std::runtime_error("No seed was found where seed was expected");
        }

        // auto bytes = new byte[field->size * field->size];
        auto bytes = std::make_unique<byte[]>(field->size * field->size);
        auto read_count = fread_s(
            bytes.get(),
            field->size * field->size,
            1,
            field->size * field->size,
            save_file
        );

        if(read_count != field->size * field->size)
        {
            CLOSE_SAVE;
            return new std::runtime_error(
                std::format(
                    "Could only read {} bytes of data where there should have been {} bytes of data", 
                    read_count, field->size * field->size
                )
            );
        }

        field->cells = std::make_unique<std::unique_ptr<Cell[]>[]>(field->size * field->size);
        for(std::size_t i = 0; i < field->size; i++)
        {
            field->cells[i] = std::make_unique<Cell[]>(field->size);

            for(std::size_t j = 0; j < field->size; j++)
            {
                std::size_t index = i * field->size + j;
                field->cells[i][j] = Cell(bytes[index]);
            }
        }

        CLOSE_SAVE;
        return field;
    }

} // namespace field
