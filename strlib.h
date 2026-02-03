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

size_t str_len(const char* s);
str str_grow(str s, size_t len);
str str_new(const char* src);
void str_free(str s);
size_t str_h_len(str s);
size_t str_h_cap(str s);
str str_concat_len(str s, const char* src, size_t len);
str str_concat(str s, const char* src);
str str_fmt(str _s, char * fmt, ...);
str str_delete(str s, size_t pos);
str str_trim(str s);
int str_find_sub(str s, const char* substr);
str str_insert(str s, const char* ins, size_t pos); // returns the same string if position overflows
str str_replace(str s, const char* dest, const char* src);
str* str_split(str s, const char* sep, int* elements); // free up to caller

#endif // strlib_h
