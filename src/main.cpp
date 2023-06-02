#include <iostream>
#include <ostream>
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

    while((io::console_input >> input) != io::key_esc)
    {
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
            std::cout << "special-value: " << input.get_value();
            std::cout << CSI_S"m" << std::endl;
            continue;
        }

        std::cout << "non-special-value: "
        << input.get_value()
        << " (" << (char)input.get_value() << ")"
        << std::endl;
    }

    std::cout << CSI_S"?1049l";

    io::console_input.restore();
    ansi::disable_ansi();
    return EXIT_SUCCESS;
}