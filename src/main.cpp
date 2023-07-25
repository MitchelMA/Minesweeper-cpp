#include <iostream>
#include <sstream>
#include "tools/consoleinput.hpp"
#include "tools/ansi.hpp"
#include "tools/dirio.hpp"
#include "field/playfield.hpp"

static std::unique_ptr<field::Playfield> playfield(std::make_unique<field::Playfield>());
static io::ConsoleInputValue input;


#define SAVE_FILE_NAME "save"
#define SAVE_FILE_EXTENSION ".bin"
static std::string save_file_location = io::join(io::exe_dir, SAVE_FILE_NAME SAVE_FILE_EXTENSION);

void init_field(int argc);
void handle_argv(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    playfield->size = STAND_FIELD_SIZE;
    playfield->bombpercentage = STAND_BOMB_PERCENTAGE;

    handle_argv(argc, argv);
    init_field(argc);

    ansi::enable_ansi();
    io::console_input.init();

    // Enter alternative buffer
    std::cout << CSI_S"?1049h";
    // Force cursor to position [1,1]
    std::cout << CSI_S"1;1H";

    std::cout << "Seed: " << playfield->seed << "\n\n";

    std::cout << playfield->as_text();
    io::console_input >> input;

    // Exit alternative buffer
    std::cout << CSI_S"?1049l";

    io::console_input.restore();
    ansi::disable_ansi();
    return EXIT_SUCCESS;
}

void init_field(int argc)
{
    if(argc > 1)
        return;

    auto result = field::Playfield::from_file(save_file_location);
    result.match(
        [](std::unique_ptr<field::Playfield> value) {
            value.swap(playfield);
            if(playfield->cells != nullptr)
                return;

            playfield->seed = 0;
            playfield->set_cells();
        },
        [](auto error) {
            std::cerr << error->what() << std::endl;

            playfield->seed = 0;
            playfield->set_cells();
        }
    );
}

void handle_argv(int argc, const char* argv[])
{
    std::stringstream ss;
    if(argc == 1)
        return;
    
    if(argc > 1)
    {
        argv++;
        ss << *argv;
        ss >> playfield->size;
        if(playfield->size < 4)
            playfield->size = STAND_FIELD_SIZE;
        std::cout << "set size to: " << playfield->size << std::endl;
        ss.clear();
    }

    if(argc > 2)
    {
        argv++;
        ss << *argv;
        ss >> playfield->bombpercentage;
        if(playfield->bombpercentage <= 0 || playfield->bombpercentage > 100)
            playfield->bombpercentage = STAND_BOMB_PERCENTAGE;
        std::cout << "set bomb-percentage to: " << playfield->bombpercentage << std::endl;
        ss.clear();
    }

    if(argc > 3)
    {
        argv++;
        ss << *argv;
        ss >> playfield->seed;
        std::cout << "set seed to: " << playfield->seed << std::endl;
        ss.clear();
    }

    playfield->set_cells();
}