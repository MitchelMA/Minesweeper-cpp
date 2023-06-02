#include <iostream>
#include "tools/consoleinput.hpp"
#include "tools/ansi.hpp"
#include "tools/dirio.hpp"

int main(void)
{
    ansi::enable_ansi();
    io::console_input.init();
    std::cout << CSI_S"?1049h";

    std::cout << "executing directory: " << io::exe_dir << std::endl;

    io::ConsoleInputValue input;
    auto q = io::ConsoleInputValue{'q', false};

    while((io::console_input >> input) != q) 
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

    std::cout << CSI_S"?1049l";

    io::console_input.restore();
    ansi::disable_ansi();
    return EXIT_SUCCESS;
}