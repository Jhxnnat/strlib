#include <stdio.h>
#include <stdbool.h>
#include "strlib.h"

#define STR_GROW_FACTOR 2

#define str_header(__s) ((void*)((__s)-(sizeof(struct string_t))))

size_t str_len(const char* s) {
	size_t i = 0;
	while (s[i] != '\0') { i++; }
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

str str_new(const char* src) {
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

void str_free(str s) {
    free((char*)s-sizeof(struct string_t));
}

size_t str_h_len(str s) {
	return ((struct string_t *)((s)-(sizeof(struct string_t))))->len;
}

size_t str_h_cap(str s) {
	return ((struct string_t *)((s)-(sizeof(struct string_t))))->cap;
}

str str_concat_len(str s, const char* src, size_t len) {
	size_t c_len = str_h_len(s);
	s = str_grow(s, len);
	if (s == NULL) return NULL;
	str_n_copy(s+c_len, src, len);
	str_set_len(s, c_len+len);
	s[c_len+len] = '\0';
	return s;
}

str str_concat(str s, const char* src) {
	return str_concat_len(s, src, str_len(src));
}

str strfmt(str _s, char * fmt, ...) {
	va_list args;
	va_start(args, fmt);

	int fmt_len = vsnprintf(NULL, 0, fmt, args);

	va_start(args, fmt);
	char s[fmt_len+1];
	int __len = vsnprintf(s, fmt_len+1, fmt, args);
	va_end(args);

	return (str_concat_len(_s, s, fmt_len));
}

str str_delete(str s, size_t pos) {
	struct string_t *h = str_header(s);
	if (h->len == 0 || pos > h->len) return NULL;
	s[pos] = 0;
	for (size_t i = pos; i < h->len; i++) {
		s[i] = s[i+1];
	}
	h->len--;
	return s;
}

str str_trim(str s) {
	size_t len = str_h_len(s);
	size_t i = 0;
	while (i < len) {
		if (char_is_space(s[i]))
			s = str_delete(s, i);
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

str str_insert(str s, const char* ins, size_t pos) {
	size_t s_cap = str_h_cap(s);
	size_t s_len = str_h_len(s);
	size_t ins_len = str_len(ins);

	if (pos > s_len) return NULL;

	size_t space = str_get_space(s);
	if (space < ins_len) {
		size_t grow_size = ins_len - space;
		s = str_grow(s, grow_size);
	}

	// move to the right (right to left)
	size_t final_len = s_len + ins_len;
	for (size_t i = final_len; i >= pos+ins_len; i--) {
		s[i] = s[i-ins_len];
	}
	// insert
	for (size_t i = pos; i < ins_len+pos; i++) {
		s[i] = ins[i-pos];
	}

	str_set_len(s, final_len);
	s[str_h_len(s)] = '\0';

	return s;
}

str str_replace(str s, const char* dest, const char* src) {
	size_t pos = (size_t)str_find_sub(s, dest);
	if (pos < 0)
		return s;
	size_t dest_len = str_len(dest);
	size_t src_len = str_len(src);

	// insert text then delete remaining text
	s = str_insert(s, src, pos);
	for (size_t i = 0; i < dest_len; i++) {
		s = str_delete(s, pos+src_len);
	}

	return s;
}

str* str_split(str s, const char* sep, int* elements) {
	size_t sep_len = str_len(sep);
	size_t s_len = str_len(s);

	int index_list[128] = {0};
	int index_pos = 0;
	int index_acum = 0;
	int index;
	//TODO: if we split 2 times, then the list would be len=3
	// so the last on the list is being ignored
	while (true) {
		int index = str_find_sub(s+index_acum, sep);
		if (index < 0) break;
		index_acum += index+sep_len;
		index_list[index_pos++] = index_acum-sep_len;
		printf(">>index: %d, %s\n", index, s+index_acum);
	}

	printf("index pos: %d\n", index_pos);
	*elements = index_pos;
	str* str_list = malloc(sizeof(struct string_t)*index_pos);
	for (int i = 0; i < index_pos; i++) {
		str_list[i] = str_new("");
		if (i == 0) {
			str_list[i] = str_concat_len(str_list[i], s, index_list[i]);
			continue;
		}
		str_list[i] = str_concat_len(str_list[i], s+index_list[i-1]+sep_len, index_list[i] - index_list[i-1] - sep_len);
	}

	for (int i = 0; i < *elements; i++) {
		printf("string: %s; len:%zu\n", str_list[i], str_len(str_list[i]));
	}
	return str_list;
}
