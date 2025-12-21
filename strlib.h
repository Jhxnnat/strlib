#ifndef strlib_h
#define strlib_h

#include <stdlib.h>
#include <stdarg.h>

typedef char* str;

struct __attribute__((packed)) string_t {
	size_t len;
	size_t cap;
	char s[];
};

// return the lenght of a string (or char*).
size_t str_len(const char* s);

// allocates more memory for the given string and returns it
str str_grow(str s, size_t len);

// return a new string
str str_new(const char* src);

// free the string
void str_free(str s);

size_t str_h_len(str s);
size_t str_h_cap(str s);
str str_concat_len(str s, const char* src, size_t len);
str str_concat(str s, const char* src);
str str_fmt(str _s, char * fmt, ...);
str str_delete(str s, size_t pos);

// return string without whitespace
str str_trim(str s);

// returns start pos of substr, (-1) if not found
int str_find_sub(str s, const char* substr);

// inserts a string at a given position and returns it. return the same string if position overflows
str str_insert(str s, const char* ins, size_t pos);

// replaces a substring with anoter
str str_replace(str s, const char* dest, const char* src);

// unimplemented
str* str_split(str s, const char* sub, size_t ret_len); // caller frees

#endif // strlib_h
