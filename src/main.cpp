#include <iostream>
#include <sstream>
#include <csignal>
#include "tools/consoleinput.hpp"
#include "tools/ansi.hpp"
#include "tools/dirio.hpp"
#include "field/playfield.hpp"

static std::unique_ptr<field::Playfield> playfield(std::make_unique<field::Playfield>());

#define SAVE_FILE_NAME "save"
#define SAVE_FILE_EXTENSION ".bin"
static std::string save_file_location = io::join(io::exe_dir, SAVE_FILE_NAME SAVE_FILE_EXTENSION);

void init_field(int argc);
void handle_argv(int argc, const char* argv[]);
void handle_exit_code(int code) noexcept;
void handle_user_exit() noexcept;
void handle_gameover() noexcept;
void handle_win() noexcept;
void handle_error() noexcept;
void signal_handler(int code) noexcept;
void handle_write(const field::Playfield& field, bool save_cells) noexcept;

int main(int argc, const char* argv[])
{
    signal(SIGSEGV, signal_handler);
    signal(SIGINT, signal_handler);

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

    // run the main-loop
    int exit_code = playfield->run();
    std::cout << "\n";
    handle_exit_code(exit_code);
    io::console_input.get_input();

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

    field::Playfield::from_file(save_file_location).match(
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

void
handle_exit_code(int code)
noexcept
{
    switch (code)
    {
        case 1:
            handle_user_exit();
            break;
        case 2:
            handle_gameover();
            break;
        case 3:
            handle_win();
            break;
        case 4:
            handle_error();
            break;
        default:
            std::cout << "Unexpected exit-code!" << " (" << code << ")" << std::endl;
    };
}

void
handle_user_exit()
noexcept
{
    std::cout << "Bedankt voor het spelen van Minesweeper!" << std::endl;
    handle_write(*playfield, true);
}

void
handle_gameover()
noexcept
{
    std::cout << CSI_S FIELD_PRINT_Y ";" FIELD_PRINT_X "H";
    std::cout << playfield->peek() << "\n\n";
    std::cout << "Wat jammer, je raakte een bom!" << std::endl;
    handle_write(*playfield, false);
}

void
handle_win()
noexcept
{
    std::cout << CSI_S FIELD_PRINT_Y ";" FIELD_PRINT_X "H";
    std::cout << playfield->peek() << "\n\n";
    std::cout << "Je hebt gewonnen!!" << std::endl;
    handle_write(*playfield, false);
}

void
handle_error()
noexcept
{
    std::cout << "Er is iets mis gegaan!" << std::endl;
    handle_write(*playfield, true);
}

void
handle_write(
    const field::Playfield& field,
    bool save_cells
) noexcept
{
    field.write_to_file(save_file_location, save_cells).match(
        [](const int && status)
        {
            std::cout << "Succesvol het spel opgeslagen met code: " << status << std::endl;
        },
        [](auto error)
        {
            std::cerr << "Something went wrong while trying to write to save-file: " << error->what() << std::endl;
        }
    );
}


void
signal_handler(int code)
noexcept
{
    switch(code)
    {
        case SIGINT:
        {
            playfield->exit_code = 1;
        }
        break;
        case SIGSEGV:
        {
            playfield->exit_code = 4;
        }
        break;
        default:
            break;
    }
}