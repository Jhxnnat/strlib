#include <stdio.h>
#include "strlib.h"

int main(void) {
	// str s = str_new("a minecraftr\n world...");
	// s = str_concat(s, ".....");
	// printf("%s\n", s);
	// s = str_delete(s, 1);
	// printf("%s\n", s);
	// s = str_trim(s);
	// printf("%s\n", s);
	// printf("sub pos: %d", str_find_sub(s, "craft"));

	// str s = str_new("12345");
	// s = str_insert(s, "..", 0);

	// str s = str_new("the owl hi!");
	// s = str_replace(s, "owl", "catito");
	// printf("%s; len:%zu\n", s, str_len(s));

	str s = str_new("qwerty..asd..zxcv..this_is_ignored..not actually");
	int elements = 0;
	str* slist = str_split(s, "..", &elements);
	printf("elements: %d\n", elements);
	for (int i = 0; i < elements; i++) {
		printf("string: %s; len:%zu\n", slist[i], str_len(slist[i]));
	}
	str_free(s);
	return 0;
}
