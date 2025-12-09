#include <stdio.h>
#include "strlib.h"

int main(void) {
	str s = strnew("a minecraftr\n world...");
	s = strconcat(s, ".....");
	printf("%s\n", s);
	s = strdelete(s, 1);
	printf("%s\n", s);
	s = strtrim(s);
	printf("%s\n", s);
	printf("sub pos: %d", str_find_sub(s, "craft"));
	strfree(s);
	return 0;
}

