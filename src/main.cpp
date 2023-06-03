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