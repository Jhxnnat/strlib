#ifndef strlib_h
#define strlib_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef char* strt;

struct __attribute__((packed)) string_t {
	size_t len;
	size_t cap;
	char s[];
};

strt strnew(const char* src);
void strfree(strt s);
size_t strtlen(const strt s);
strt strtcatlen(strt s, const char* src, size_t len);
strt strcat(strt s, const char* src);

strt strt_grow(strt s, size_t len);

// strt strfmt(strt _s, char * fmt, ...);

#endif // strlib_h
