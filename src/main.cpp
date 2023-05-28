#include <iostream>
#include "io/io.hpp"
#include "ansi/ansi.hpp"

int main(void)
{
    ansi::enable_ansi();
    io::console_input.init();
    std::cout << "Hello, World!" << std::endl;

    io::ConsoleInputValue input;

    while((input = io::console_input.get_input()) != io::key_esc)
    {
        if(input.special) 
        {
            std::cout << CSI"31m";
            std::cout << "special-value: " << input.value;
            std::cout << CSI"m" << std::endl;
            continue;
        }

        std::cout << "non-special-value: "
        << input.value
        << " (" << (char)input.value << ")" 
        << std::endl;
    }

    io::console_input.restore();
    ansi::disable_ansi();
    return EXIT_SUCCESS;
}