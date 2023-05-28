#ifndef _ANSI_HPP
#define _ANSI_HPP

#define CSI "\x1b["

namespace ansi
{

    unsigned long enable_ansi();
    unsigned long disable_ansi();

} // namespace ansi

#endif // !_ANSI_HPP