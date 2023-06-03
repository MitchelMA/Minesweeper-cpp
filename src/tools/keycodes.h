#ifndef _KEYCODES_H
#define _KEYCODES_H

#include <limits.h>
#include <cstdint>

#define KEYCODE_UNSET 0

#define KEYCODE_ARROW_UP    KEYCODE_UNSET
#define KEYCODE_ARROW_RIGHT KEYCODE_UNSET
#define KEYCODE_ARROW_DOWN  KEYCODE_UNSET
#define KEYCODE_ARROW_LEFT  KEYCODE_UNSET

#define KEYCODE_F1  KEYCODE_UNSET
#define KEYCODE_F2  KEYCODE_UNSET
#define KEYCODE_F3  KEYCODE_UNSET
#define KEYCODE_F4  KEYCODE_UNSET
#define KEYCODE_F5  KEYCODE_UNSET
#define KEYCODE_F6  KEYCODE_UNSET
#define KEYCODE_F7  KEYCODE_UNSET
#define KEYCODE_F8  KEYCODE_UNSET
#define KEYCODE_F9  KEYCODE_UNSET
#define KEYCODE_F10 KEYCODE_UNSET
#define KEYCODE_F11 KEYCODE_UNSET
#define KEYCODE_F12 KEYCODE_UNSET

#define KEYCODE_INSERT KEYCODE_UNSET
#define KEYCODE_HOME   KEYCODE_UNSET
#define KEYCODE_PGUP   KEYCODE_UNSET
#define KEYCODE_DEL    KEYCODE_UNSET
#define KEYCODE_END    KEYCODE_UNSET
#define KEYCODE_PGDN   KEYCODE_UNSET

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#undef KEYCODE_ARROW_UP
#undef KEYCODE_ARROW_RIGHT
#undef KEYCODE_ARROW_DOWN
#undef KEYCODE_ARROW_LEFT

#undef KEYCODE_F1
#undef KEYCODE_F2
#undef KEYCODE_F3
#undef KEYCODE_F4
#undef KEYCODE_F5
#undef KEYCODE_F6
#undef KEYCODE_F7
#undef KEYCODE_F8
#undef KEYCODE_F9
#undef KEYCODE_F10
#undef KEYCODE_F11
#undef KEYCODE_F12

#undef KEYCODE_INSERT
#undef KEYCODE_HOME
#undef KEYCODE_PGUP
#undef KEYCODE_DEL
#undef KEYCODE_END
#undef KEYCODE_PGDN

// ---------------------- //

#define KEYCODE_ARROW_UP    72, true
#define KEYCODE_ARROW_RIGHT 77, true
#define KEYCODE_ARROW_DOWN  80, true
#define KEYCODE_ARROW_LEFT  75, true

#define KEYCODE_F1   59, true
#define KEYCODE_F2   60, true
#define KEYCODE_F3   61, true
#define KEYCODE_F4   62, true
#define KEYCODE_F5   63, true
#define KEYCODE_F6   64, true
#define KEYCODE_F7   65, true
#define KEYCODE_F8   66, true
#define KEYCODE_F9   67, true
#define KEYCODE_F10  68, true
#define KEYCODE_F11 133, true
#define KEYCODE_F12 134, true

#define KEYCODE_INSERT 82, true
#define KEYCODE_HOME   71, true
#define KEYCODE_PGUP   73, true
#define KEYCODE_DEL    83, true
#define KEYCODE_END    79, true
#define KEYCODE_PGDN   81, true

#elif defined(__linux__)

#define _SET_KEYCODE_1(a) (std::uint64_t)a
#define _SET_KEYCODE_2(a, b) _SET_KEYCODE_1(a) | ((std::uint64_t)b << CHAR_BIT)
#define _SET_KEYCODE_3(a, b, c) _SET_KEYCODE_2(a, b) | ((std::uint64_t)c << CHAR_BIT*2)
#define _SET_KEYCODE_4(a, b, c, d) _SET_KEYCODE_3(a, b, c) | ((std::uint64_t)d << CHAR_BIT*3)
#define _SET_KEYCODE_5(a, b, c, d, e) _SET_KEYCODE_4(a, b, c, d) | ((std::uint64_t)e << CHAR_BIT*4)
#define _SET_KEYCODE_6(a, b, c, d, e, f) _SET_KEYCODE_5(a, b, c, d, e) | ((std::uint64_t)f << CHAR_BIT*5)
#define _SET_KEYCODE_7(a, b, c, d, e, f, g) _SET_KEYCODE_6(a, b, c, d, e, f) | ((std::uint64_t)g << CHAR_BIT*6)

#define SET_KEYCODE_1(a) _SET_KEYCODE_1(a), 1
#define SET_KEYCODE_2(a, b) _SET_KEYCODE_2(a, b), 2
#define SET_KEYCODE_3(a, b, c) _SET_KEYCODE_3(a, b, c), 3
#define SET_KEYCODE_4(a, b, c, d) _SET_KEYCODE_4(a, b, c, d), 4
#define SET_KEYCODE_5(a, b, c, d, e) _SET_KEYCODE_5(a, b, c, d, e), 5
#define SET_KEYCODE_6(a, b, c, d, e, f) _SET_KEYCODE_6(a, b, c, d, e, f), 6
#define SET_KEYCODE_7(a, b, c, d, e, f, g) _SET_KEYCODE_7(a, b, c, d, e, f, g), 7


#undef KEYCODE_F1
#undef KEYCODE_F2
#undef KEYCODE_F3
#undef KEYCODE_F4
#undef KEYCODE_F5
#undef KEYCODE_F6
#undef KEYCODE_F7
#undef KEYCODE_F8
#undef KEYCODE_F9
#undef KEYCODE_F10
#undef KEYCODE_F11
#undef KEYCODE_F12

#undef KEYCODE_INSERT
#undef KEYCODE_HOME
#undef KEYCODE_PGUP
#undef KEYCODE_DEL
#undef KEYCODE_END
#undef KEYCODE_PGDN

#undef KEYCODE_ARROW_UP
#undef KEYCODE_ARROW_RIGHT
#undef KEYCODE_ARROW_DOWN
#undef KEYCODE_ARROW_LEFT

// ---------------------- //

/*
[first   degree value],
[second  degree value],
[third   degree value],
[fourth  degree value],
[fifth   degree value],
[sixth   degree value],
[seventh degree value],
[degree count]
*/

#define KEYCODE_ARROW_UP    SET_KEYCODE_3(27, 91, 65)
#define KEYCODE_ARROW_RIGHT SET_KEYCODE_3(27, 91, 67)
#define KEYCODE_ARROW_DOWN  SET_KEYCODE_3(27, 91, 66)
#define KEYCODE_ARROW_LEFT  SET_KEYCODE_3(27, 91, 68)

#define KEYCODE_F1           SET_KEYCODE_3(27, 79, 80)
#define KEYCODE_F2           SET_KEYCODE_3(27, 79, 81)
#define KEYCODE_F3           SET_KEYCODE_3(27, 79, 82)
#define KEYCODE_F4           SET_KEYCODE_3(27, 79, 83)
#define KEYCODE_F5  SET_KEYCODE_5(27, 91, 49, 53, 126)
#define KEYCODE_F6  SET_KEYCODE_5(27, 91, 49, 55, 126)
#define KEYCODE_F7  SET_KEYCODE_5(27, 91, 49, 56, 126)
#define KEYCODE_F8  SET_KEYCODE_5(27, 91, 49, 57, 126)
#define KEYCODE_F9  SET_KEYCODE_5(27, 91, 50, 48, 126)
#define KEYCODE_F10 SET_KEYCODE_5(27, 91, 50, 49, 126)
#define KEYCODE_F11 SET_KEYCODE_5(27, 91, 50, 51, 126)
#define KEYCODE_F12 SET_KEYCODE_5(27, 91, 50, 52, 126)

#define KEYCODE_INSERT SET_KEYCODE_4(27, 91, 50, 126)
#define KEYCODE_HOME        SET_KEYCODE_3(27, 91, 72)
#define KEYCODE_PGUP   SET_KEYCODE_4(27, 91, 53, 126)
#define KEYCODE_DEL    SET_KEYCODE_4(27, 91, 51, 126)
#define KEYCODE_END         SET_KEYCODE_3(27, 91, 70)
#define KEYCODE_PGDN   SET_KEYCODE_4(27, 91, 54, 126)

#endif // os-check

#endif // _KEYCODES_H