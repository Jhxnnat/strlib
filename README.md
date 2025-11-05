# strlib

* _This is a work in progress_

This library is inspired by the [Simple Dynamic Strings](https://github.com/antirez/sds) library.
Strings are heap allocated and have a header wich stores information like capacity and length. The rest is the actual string.
There are no uses of `string.h` header yet.

There are multiple functions, the following sources are used for inspiration:
* [GML strings](https://manual.gamemaker.io/monthly/en/index.htm?#t=GameMaker_Language%2FGML_Reference%2FStrings%2FStrings.htm).
* [raylib](https://github.com/raysan5/raylib), 

