# strlib

* _This is a work in progress_

This library is inspired by the [Simple Dynamic Strings](https://github.com/antirez/sds) library.
Strings are heap allocated and have a header that stores information like capacity and length, the rest is the actual string and can be used on std functions like printf. Also, I try not to use strlib.h header.

There are multiple functions, the following sources are used for inspiration:
* [GML strings](https://manual.gamemaker.io/monthly/en/index.htm?#t=GameMaker_Language%2FGML_Reference%2FStrings%2FStrings.htm).
* [raylib](https://github.com/raysan5/raylib), 

