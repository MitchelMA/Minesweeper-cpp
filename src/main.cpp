#include <iostream>
#include "tools/consoleinput.hpp"
#include "tools/ansi.hpp"
#include "field/cell.hpp"

int main(void)
{
    ansi::enable_ansi();
    io::console_input.init();
    std::cout << "Hello, World!" << std::endl;

    io::ConsoleInputValue input;

    while((io::console_input >> input) != io::key_esc)
    {
        if(input.special) 
        {
            std::cout << CSI_S"31m";
            std::cout << "special-value: " << input.value;
            std::cout << CSI_S"m" << std::endl;
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