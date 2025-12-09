#include <stdio.h>
#include "strlib.h"

#define STR_GROW_FACTOR 2

#define str_header(__s) ((void*)((__s)-(sizeof(struct string_t))))
#define SHD(__s) ((struct string_t*)((__s)-(sizeof(struct string_t))))

size_t str_len(const char* s) {
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

static bool char_is_space(char c) {
	return (c == ' ' || c == '\n' || c == '\t');
}

size_t str_get_space(str s) {
	struct string_t *sh = str_header(s);
	return sh->cap - sh->len;
}

void str_set_len(str s, size_t len) {
	struct string_t *sh = (struct string_t*)((s)-(sizeof(struct string_t)));
	sh->len = len;
}

str str_grow(str s, size_t len) {
	size_t header_size = sizeof(struct string_t);
	// TODO: use str_header
	struct string_t *sh = (void*)((s)-(sizeof(struct string_t)));

	size_t space = sh->cap - sh->len;
	if (space >= len) return s;

	sh = realloc(sh, header_size+sh->cap+len);
	if (sh == NULL) return NULL;
	sh->cap += len;

	return s;
}

str strnew(const char* src) {
	void *header;
	str s;

	size_t srclen = str_len(src);
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

void strfree(str s) {
    free((char*)s-sizeof(struct string_t));
}

size_t strlen(str s) {
	return ((struct string_t *)((s)-(sizeof(struct string_t))))->len;
}

size_t strcap(str s) {
	return ((struct string_t *)((s)-(sizeof(struct string_t))))->cap;
}

// TODO make use: str_n_copy(s+c_len, src, len);
str strconcatlen(str s, const char* src, size_t len) {
	size_t c_len = strlen(s);

	s = str_grow(s, len);
	if (s == NULL) return NULL;
	str_copy(s+c_len, src);
	str_set_len(s, c_len+len);
	s[c_len+len] = '\0';
	return s;
}

str strconcat(str s, const char* src) {
	return strconcatlen(s, src, str_len(src));
}

str strfmt(str _s, char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	
	int fmt_len = vsnprintf(NULL, 0, fmt, args);

	va_start(args, fmt);
	char s[fmt_len+1];
	int __len = vsnprintf(s, fmt_len+1, fmt, args);
	va_end(args);

	return (strconcatlen(_s, s, fmt_len));
}

str strdelete(str s, size_t pos) {
	struct string_t *h = str_header(s);
	if (h->len == 0 || pos > h->len) return NULL;
	s[pos] = 0;
	for (size_t i = pos; i < h->len; i++) {
		s[i] = s[i+1];
	}
	h->len--;
	return s;
}

str strtrim(str s) {
	size_t len = strlen(s);
	size_t i = 0;
	while (i < len) {
		if (char_is_space(s[i]))
			s = strdelete(s, i);
		else i++;
	}
	return s;
}

int str_find_sub(str s, const char* substr) {
	size_t len = str_len(s);
	size_t sub_len = str_len(substr);
	size_t j = 0;
	for (size_t i = 0; i < len; i++) {
		while (s[i+j] == substr[j]) {
			if (++j >= sub_len) return i;
		}
	}
	return -1;
}

str strreplace(str s, const char* dest, const char* src) {
	return s;
}

