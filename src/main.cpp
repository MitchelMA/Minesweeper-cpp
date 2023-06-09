#include <iostream>
#include <memory>
#include "tools/consoleinput.hpp"
#include "tools/ansi.hpp"
#include "tools/dirio.hpp"
#include "field/playfield.hpp"

static std::unique_ptr<field::Playfield> playfield(new field::Playfield);


#define SAVE_FILE_NAME "save.bin"
static std::string save_file_location = io::join(io::exe_dir, SAVE_FILE_NAME);

void init_field(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    ansi::enable_ansi();
    io::console_input.init();
    std::cout << CSI_S"?1049h";

    std::cout << "executing directory: " << io::exe_dir << std::endl;

    io::ConsoleInputValue input;

    init_field(argc, argv);

    while((io::console_input >> input) != io::key_esc)
    {

    #if defined(__linux__)

        std::uint8_t* bytes = (std::uint8_t*)&input.value;
        for(std::size_t i = 0; i < input.degree; i++)
            std::cout << "[" << (int)bytes[i] << "]";
        std::cout << std::endl;

    #endif // linux-check

        if(input == io::key_arrow_up)
            std::cout << "arrow-up" << std::endl;

        if(input == io::key_arrow_right)
            std::cout << "arrow-right" << std::endl;

        if(input == io::key_arrow_down)
            std::cout << "arrow-down" << std::endl;

        if(input == io::key_arrow_left)
            std::cout << "arrow-left" << std::endl;

        if(input.is_special())
        {
            std::cout << CSI_S"31m";
            std::cout << "special-value: " << input.value;
            std::cout << CSI_S"m\n" << std::endl;
            continue;
        }

        std::cout << "non-special-value: "
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
        << input.get_value()
    #endif
        << " (" << (char)input.get_value() << ")\n"
        << std::endl;
    }

    std::cout << CSI_S"?1049l";

    io::console_input.restore();
    ansi::disable_ansi();
    return EXIT_SUCCESS;
}

void init_field(int argc, char* argv[])
{
    bool successful = false;
    auto result = field::Playfield::from_file(save_file_location);
    result.match(
        [&successful](std::unique_ptr<field::Playfield> value) {
            value.swap(playfield);
            if(playfield->cells.get() != nullptr)
                return;

            playfield->seed = 0;
            playfield->set_cells();
            successful = true;
        },
        [](auto error) {
            std::cerr << error->what() << std::endl;
        }
    );

    if(successful)
        return;

        
    
}