#ifndef _ANSI_HPP
#define _ANSI_HPP

#define ESC_S "\x1b"
#define CSI_S ESC_S"["

namespace ansi
{

    unsigned long enable_ansi();
    unsigned long disable_ansi();

} // namespace ansi

#endif // !_ANSI_HPP