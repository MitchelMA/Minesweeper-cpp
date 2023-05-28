#include <iostream>
#include "io/io.hpp"

int main(void)
{
    io::console_input.init();
    std::cout << "Hello, World!" << std::endl;

    io::ConsoleInputValue input;

    while((input = io::console_input.get_input()) != io::key_esc)
    {
        if(input.special) 
        {
            std::cout << "special-value: " << input.value << std::endl; 
            continue;
        }

        std::cout << "non-special-value: "
        << input.value
        << " (" << (char)input.value << ")" 
        << std::endl;
    }

    io::console_input.restore();
    return EXIT_SUCCESS;
}