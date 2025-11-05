#include "strlib.h"

int main(void) {
	strt s = strnew("Loremp.");
	s = strtcat(s, " Ipsum.");
	printf("%s - %d\n", s, strtlen(s));

	strt s2 = strnew("Magic nums: ");
	s2 = strfmt(s2, "([%zu]) | %s", 77, s);
	printf("%s\n", s2);

	strfree(s);
	strfree(s2);
	return 0;
}

