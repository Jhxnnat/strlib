# strlib

* _This is a work in progress_

C string library without using `string.h` header.

This library is inpired by the [Simple Dynamic Strings](https://github.com/antirez/sds) library in a even simplier way.
Strings are heap allocated and have a header wich stores information like capacity and length. The rest is the actual string.

There are multiple functions, the following sources are used for inspiration:
* [GML strings](https://manual.gamemaker.io/monthly/en/index.htm?#t=GameMaker_Language%2FGML_Reference%2FStrings%2FStrings.htm).
* [raylib](https://github.com/raysan5/raylib), 

