#ifndef strlib_h
#define strlib_h

// TODO: make test.c, assert all the functions work as intended

#include <stdlib.h>
#include <stdarg.h>

typedef char* str;

struct __attribute__((packed)) string_t {
	size_t len;
	size_t cap;
	char s[];
};

size_t str_len(const char* s);

str str_grow(str s, size_t len);

//TODO: use snake case for all functions
str strnew(const char* src);
void strfree(str s);
size_t strlen(const str s); //TODO: unuse this, use strheader instead for this
str strconcatlen(str s, const char* src, size_t len);
str strconcat(str s, const char* src);
str strfmt(str _s, char * fmt, ...);
str strdelete(str s, size_t pos);
str strtrim(str s);
int str_find_sub(str s, const char* substr); // returns start pos of substr, (-1) if not found

str str_insert(str s, const char* ins, size_t pos);
str strreplace(str s, const char* dest, const char* src);
str* strsplit(str s, const char* sub, size_t ret_len);

#endif // strlib_h
