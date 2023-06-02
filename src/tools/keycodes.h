#ifndef _KEYCODES_H
#define _KEYCODES_H

#define KEYCODE_UNSET -1

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

#define KEYCODE_ARROW_UP    27, 91, 65, 0, 0, 0, 0, 3
#define KEYCODE_ARROW_RIGHT 27, 91, 67, 0, 0, 0, 0, 3
#define KEYCODE_ARROW_DOWN  27, 91, 66, 0, 0, 0, 0, 3
#define KEYCODE_ARROW_LEFT  27, 91, 68, 0, 0, 0, 0, 3

#define KEYCODE_F1     27, 79, 80, 0, 0, 0, 0, 3
#define KEYCODE_F2     27, 79, 81, 0, 0, 0, 0, 3
#define KEYCODE_F3     27, 79, 82, 0, 0, 0, 0, 3
#define KEYCODE_F4     27, 79, 83, 0, 0, 0, 0, 3
#define KEYCODE_F5  27, 91, 49, 53, 126, 0, 0, 5
#define KEYCODE_F6  27, 91, 49, 55, 126, 0, 0, 5
#define KEYCODE_F7  27, 91, 49, 56, 126, 0, 0, 5
#define KEYCODE_F8  27, 91, 49, 57, 126, 0, 0, 5
#define KEYCODE_F9  27, 91, 50, 48, 126, 0, 0, 5
#define KEYCODE_F10 27, 91, 50, 49, 126, 0, 0, 5
#define KEYCODE_F11 27, 91, 50, 51, 126, 0, 0, 5
#define KEYCODE_F12 27, 91, 50, 52, 126, 0, 0, 5

#define KEYCODE_INSERT 27, 91, 50, 126, 0, 0, 0, 4
#define KEYCODE_HOME     27, 91, 72, 0, 0, 0, 0, 3
#define KEYCODE_PGUP   27, 91, 53, 126, 0, 0, 0, 4
#define KEYCODE_DEL    27, 91, 51, 126, 0, 0, 0, 4
#define KEYCODE_END      27, 91, 70, 0, 0, 0, 0, 3
#define KEYCODE_PGDN      27, 91, 54, 126, 0, 0, 4

#endif // os-check

#endif // _KEYCODES_H