#include "strlib.h"

int main(void) {
	strt s = strnew("Loremp.");
	s = strtcatlen(s, " Ipsum.", 7);
	printf("%s - %d\n", s, strtlen(s));

	// strt s2;
	// s2 = strfmt(s2, "dolor sit(%d) amet magic.", 77);
	// printf("%s\n", s2);

	// s2 = strupper(s2);
	// s2 = strdelete(s2, 5, 5);
	//
	// strt s3 = strnew("not in #pascal case!");
	// strt s4 = strpascal(s3);
	//
	strfree(s);
	// strfree(s2);
	// strfree(s3);
	// strfree(s4);
	return 0;
}
