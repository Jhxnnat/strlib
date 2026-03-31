# strlib

Small strings implementation inspired by the [Simple Dynamic Strings](https://github.com/antirez/sds) library.
Strings are heap allocated, a header stores information like capacity and length, the rest is the actual string and it can be used with standart functions like printf.
Examples are on main.c

The following sources are used as inspiration for functions that I could implement:
* [GML strings](https://manual.gamemaker.io/monthly/en/index.htm?#t=GameMaker_Language%2FGML_Reference%2FStrings%2FStrings.htm).
* [raylib](https://github.com/raysan5/raylib).

