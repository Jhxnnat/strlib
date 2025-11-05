#include "strlib.h"

#define STR_GROW_FACTOR 2

#define strt_header(__s) (void*)((__s)-(sizeof(struct string_t)))

static size_t str_len(const char* s) {
	size_t i = 0;
	while (s[++i] != '\0');
	return i;
}

static char *str_n_copy(char* d, const char* s, size_t len) {
	char *_r = d;
	for (size_t i = 0; i < len; i++) {
		*d++ = *s++;
	}
	*d = 0;
	return _r;
}

static char *str_copy(char* d, const char* s) {
	char *_r = d;
	while (*s) {
		*d++ = *s++;
	}
	*d = 0;
	return _r;
}

static void str_set(char* dest, int c, size_t n) {
	for (size_t i = 0; i<n; ++i) {
		dest[i] = c;
	}
}

size_t strt_get_space(strt s) {
	struct string_t *sh = strt_header(s);
	return sh->cap - sh->len;
}

strt strt_grow(strt s, size_t len) {
	size_t header_size = sizeof(struct string_t);
	struct string_t *header = strt_header(s);
	size_t space = header->cap - header->len;
	if (space >= len) return s;

	header->cap += len;
	size_t newcap = header->cap;

	header = realloc(header, header_size+newcap);
	if (header == NULL) return NULL;
	return s;
}

strt strnew(const char* src) {
	void *header;
	strt s;

	int srclen = str_len(src);
	int headerlen = sizeof(struct string_t);
	header = malloc(headerlen+srclen);
	
	s = (char*)header+headerlen;

	struct string_t *sh = (void*)((s)-(sizeof(struct string_t)));
	sh->len = srclen;
	sh->cap = srclen;

	if (src && srclen) {
		str_copy(s, src);
	} else {
		str_set(s, 0, srclen);
	}
	s[srclen] = '\0';
	return s;
}

void strfree(strt s) {
    free((char*)s-sizeof(struct string_t));
}

size_t strtlen(const strt s) {
	return ((struct string_t *)((s)-(sizeof(struct string_t))))->len;
}

strt strtcatlen(strt s, const char* src, size_t len) {
	size_t s_len = strtlen(s);
	
	s = strt_grow(s, len);
	if (s == NULL) return NULL;

	// str_n_copy(s+s_len, src, len);
	struct string_t *h = strt_header(s);
	str_copy(s+h->len, src);
	h->len += s_len;
	s[s_len+len] = '\0';
	return s;
}

// TODO
// strt strfmt(strt _s, char * fmt, ...) {
// 	va_list ap;
// 	char* s;
// 	va_start(ap, fmt);
//
// 	va_end(ap);
// 	return s;
// }

